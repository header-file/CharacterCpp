#include "CPlayerController.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Player/CSword.h"
#include "Player/CRifle.h"
#include "Player/CBullet.h"
#include "Player/CLightning.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Effect/COnCameraShake.h"
#include "Geometry/CBrazier.h"
#include "Geometry/CSwitch.h"
#include "Sound/SoundBase.h"
#include "Enemy/CEnemy.h"

ACPlayerController::ACPlayerController()
{

}

void ACPlayerController::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ACPlayer>(GetPawn());
}

void ACPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CameraRotation();
}

void ACPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ACPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ACPlayerController::MoveRight);

	InputComponent->BindAction("Run", IE_Pressed, this, &ACPlayerController::Running);
	InputComponent->BindAction("Run", IE_Released, this, &ACPlayerController::Walking);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACPlayerController::Jump);

	InputComponent->BindAxis("CameraPitch", this, &ACPlayerController::CameraPitch);
	InputComponent->BindAxis("CameraYaw", this, &ACPlayerController::CameraYaw);

	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &ACPlayerController::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &ACPlayerController::ZoomOut);

	InputComponent->BindAction("Equip", EInputEvent::IE_Pressed, this, &ACPlayerController::Equip);
	
	InputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &ACPlayerController::Attack);
	InputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &ACPlayerController::Shoot);
	InputComponent->BindAction("Shoot", EInputEvent::IE_Released, this, &ACPlayerController::StopVolley);
	InputComponent->BindAction("MagicCast", EInputEvent::IE_Pressed, this, &ACPlayerController::Spell);
	InputComponent->BindAction("MagicCast", EInputEvent::IE_Released, this, &ACPlayerController::Dispell);

	InputComponent->BindAction("Block", IE_Pressed, this, &ACPlayerController::Block);
	InputComponent->BindAction("Block", IE_Released, this, &ACPlayerController::UnBlock);
	InputComponent->BindAction("Aim", IE_Pressed, this, &ACPlayerController::Aim);
	InputComponent->BindAction("Aim", IE_Released, this, &ACPlayerController::UnAim);

	InputComponent->BindAction("Sit", IE_Pressed, this, &ACPlayerController::ToggleSit);

	InputComponent->BindAction("Roll", IE_Pressed, this, &ACPlayerController::Roll);
	InputComponent->BindAction("BackStep", IE_Pressed, this, &ACPlayerController::BackStep);

	InputComponent->BindAction("Reload", IE_Pressed, this, &ACPlayerController::Reload);

	InputComponent->BindAction("Climb", IE_Pressed, this, &ACPlayerController::ClimbLedge);
	InputComponent->BindAction("ExitLedge", IE_Pressed, this, &ACPlayerController::ExitLedge);
	InputComponent->BindAxis("MoveRight", this, &ACPlayerController::HangingRight);
	InputComponent->BindAction("Interact", IE_Pressed, this, &ACPlayerController::Interact);

	InputComponent->BindAction("WeaponUp", IE_Pressed, this, &ACPlayerController::WeaponUp);
	InputComponent->BindAction("WeaponDown", IE_Pressed, this, &ACPlayerController::WeaponDown);

	InputComponent->BindAction("ToggleTarget", IE_Pressed, this, &ACPlayerController::ToggleTarget);

	InputComponent->BindAction("ChangeTarget", IE_Pressed, this, &ACPlayerController::ChangeTarget);

	InputComponent->BindAction("WeaponOption", IE_Pressed, this, &ACPlayerController::WeaponOption);

	InputComponent->BindAction("Pause", IE_Pressed, this, &ACPlayerController::Pause);
}

void ACPlayerController::CameraRotation()
{
	if (!Player->GetLockOn())
	{
		//Yaw
		{
			FRotator rotation = Player->GetCameraBoom()->GetComponentRotation();
			rotation.Yaw += CameraInput.X;

			Player->GetCameraBoom()->SetWorldRotation(rotation);
		}

		//Pitch
		{

			if (FMath::IsNearlyZero(CameraInput.Y, 1e-6f) == false)
			{
				FRotator rotation = Player->GetCameraBoom()->GetComponentRotation();
				rotation.Pitch = FMath::Clamp<float>(rotation.Pitch + CameraInput.Y, -80, 60);

				Player->GetCameraBoom()->SetWorldRotation(rotation);
			}
		}
	}
	else
	{
		if (TargetEnemy == NULL) return;

		//Pitch
		{
			if (FMath::IsNearlyZero(CameraInput.Y, 1e-6f) == false)
			{
				FRotator rotation = Player->GetCameraBoom()->GetComponentRotation();
				rotation.Pitch = FMath::Clamp<float>(rotation.Pitch + CameraInput.Y, -80, 10);

				Player->GetCameraBoom()->SetWorldRotation(rotation);
			}
		}

		CalculateCameraRotation();
	}

	if (Player->GetDrawn() == true)
	{
		FRotator rot;
		rot = Player->GetTopDownCameraComponent()->GetComponentRotation();
		Player->SetActorRotation(FRotator(0.0f, rot.Yaw, 0.0f));
	}
	else
	{
		if (Player->GetHanging() == true)
			Climbing();
	}
}

void ACPlayerController::MoveForward(float Axis)
{
	bool b = true;
	b &= Player->GetCanMove() == true;

	if (b == false) return;
	
	FRotator rotator;
	rotator = Player->GetCameraBoom()->GetComponentRotation();
	FRotator forward = FRotator(0, rotator.Yaw, 0);
	FQuat quat = FQuat(forward);

	FVector vec = quat.GetForwardVector();
	Player->AddMovementInput(vec, Axis);
}

void ACPlayerController::MoveRight(float Axis)
{
	bool b = true;
	b &= Player->GetCanMove() == true;
	b &= Player->GetHanging() == false;

	if (b == false) return;
	
	FRotator rotator;
	rotator = Player->GetCameraBoom()->GetComponentRotation();
	FRotator forward = FRotator(0, rotator.Yaw, 0);
	FQuat quat = FQuat(forward);

	FVector vec = quat.GetRightVector();
	Player->AddMovementInput(vec, Axis);
}

void ACPlayerController::Walking()
{
	if (Player->GetDrawn() == true) return;

	Player->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ACPlayerController::Running()
{
	if (Player->GetDrawn() == true) return;

	Player->GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void ACPlayerController::Jump()
{
	Player->Jump();
}

void ACPlayerController::CameraPitch(float Axis)
{
	CameraInput.Y = Axis * CameraSpeed.Y;
}

void ACPlayerController::CameraYaw(float Axis)
{
	CameraInput.X = Axis * CameraSpeed.X;
}

void ACPlayerController::ZoomIn()
{
	bool b = true;
	b &= Player->GetDrawn() == false;

	if (b == false) return;

	Player->GetCameraBoom()->TargetArmLength -= ZoomFactor;
}

void ACPlayerController::ZoomOut()
{
	bool b = true;
	b &= Player->GetDrawn() == false;

	if (b == false) return;

	Player->GetCameraBoom()->TargetArmLength += ZoomFactor;
}

void ACPlayerController::Equip()
{
	if (Player->GetDrawing() == true) return;
	if (Player->GetSheathing() == true) return;
	if (Player->GetAiming() == true) return;

	if (Player->GetDrawn() == false)
	{
		if (Player->GetCharacterMovement()->IsFalling() == false)
			Equipping();
	}
	else
		Sheathing();
}

void ACPlayerController::Equipping()
{
	Player->SetDrawing(true);
	Player->SetCanMove(false);

	Player->bUseControllerRotationYaw = true;
	Player->GetCharacterMovement()->bOrientRotationToMovement = false;
	Player->GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void ACPlayerController::Sheathing()
{
	Player->SetSheathing(true);
	Player->SetCanMove(false);

	Player->bUseControllerRotationYaw = false;
	Player->GetCharacterMovement()->bOrientRotationToMovement = true;
	Player->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ACPlayerController::Attack()
{
	bool b = true;
	b &= Player->GetDrawing() == false;
	b &= Player->GetDrawn() == true;
	b &= Player->GetMelee() == true;

	if (b == false) return;

	if (Player->GetAssassin())
	{
		Cast<ACEnemy>(Player->GetAssassinateTarget())->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		SetViewTargetWithBlend(Player->GetAssassinateTarget(), 0.5f);

		FTimerHandle handle;
		GetWorld()->GetTimerManager().SetTimer(handle, this, &ACPlayerController::Assassinate, 0.5f, false, 0.5f);
	}
	else if (Player->GetDown() && !Player->GetCharacterMovement()->IsFalling())
	{
		Player->PlayAnimMontage(Player->GetDownAttackMontage());
	}
	else
	{
		if (Player->GetCharacterMovement()->IsFalling())
			Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

		if (Player->GetAttacking())
		{
			if (Player->GetCombo1())
				Player->SetCurrentCombo(1);
			else if (Player->GetCombo2())
				Player->SetCurrentCombo(2);
		}
		else
		{
			Player->PlayAnimMontage(Player->GetComboAttackMontage());
			Player->SetAttacking(true);
			Player->SetCanMove(false);
		}
	}
}

void ACPlayerController::Shoot()
{
	bool b = true;
	b &= Player->GetDrawing() == false;
	b &= Player->GetDrawn() == true;
	b &= Player->GetAttacking() == false;
	b &= Player->GetRange() == true;
	b &= Player->GetCurrentBullets() > 0;

	if (b == false) return;

	Player->SetAttacking(true);
	Player->SetCanMove(true);
	
	if (Player->GetSemiAuto())
		bSemiAuto = true;
	else
		Player->Shoot();
}

void ACPlayerController::StopVolley()
{
	if (Player->GetSemiAuto())
		bSemiAuto = false;
}

void ACPlayerController::Spell()
{
	bool b = true;
	b &= Player->GetDrawing() == false;
	b &= Player->GetDrawn() == true;
	b &= Player->GetMagic() == true;
	b &= Player->GetCurrentMP() > 0.0f;

	if (b == false) return;

	if (Player->GetChargeMagic())
	{
		if (Player->GetCurrentMP() < 10.0f) return;

		Player->PlayAnimMontage(Player->GetCastMontage());
		Player->SetCasting(true);
		Player->SetCurrentMP(Player->GetCurrentMP() - 10.0f);
	}
	else
	{
		Player->PlayAnimMontage(Player->GetSpellMontage());
		Player->SetCasting(true);
	}
}

void ACPlayerController::Dispell()
{
	bool b = true;
	b &= Player->GetCasting() == true;

	if (b == false) return;

	if (Player->GetChargeMagic())
	{
		Player->SetCasting(false);
		Player->PlayAnimMontage(Player->GetBallThrowMontage());
	}
	else
	{
		Player->StopAnimMontage(Player->GetSpellMontage());
		Player->SetCasting(false);

		if (Player->GetLightning() == NULL) return;
	}
}

void ACPlayerController::Block()
{
	bool b = true;
	b &= Player->GetDrawing() == false;
	b &= Player->GetDrawn() == true;
	b &= Player->GetAttacking() == false;
	b &= Player->GetMelee() == true;

	if (b == false) return;

	Player->SetBlocking(true);
	Player->SetCanMove(false);

	Player->SetBlockingTimer(0.0f);
}

void ACPlayerController::UnBlock()
{
	Player->SetBlocking(false);
	Player->SetCanMove(true);
}

void ACPlayerController::Aim()
{
	bool b = true;
	b &= Player->GetDrawing() == false;
	b &= Player->GetDrawn() == true;
	b &= Player->GetAttacking() == false;
	b &= (Player->GetRange() == true || Player->GetMagic() == true);
	
	if (b == false) return;

	Player->SetAiming(true);
	
	Player->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ACPlayerController::UnAim()
{
	bool b = true;
	b &= Player->GetDrawing() == false;
	b &= Player->GetDrawn() == true;
	b &= Player->GetAttacking() == false;
	b &= (Player->GetRange() == true || Player->GetMagic() == true);

	if (b == false) return;

	Player->SetAiming(false);

	Player->GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void ACPlayerController::ToggleSit()
{
	bool b = true;
	b &= Player->GetDrawing() == false;
	b &= Player->GetDrawn() == true;
	b &= Player->GetSheathing() == false;

	if (b == false) return;

	Player->SetSit(!Player->GetSit());

	if (Player->GetSit())
	{
		Player->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		Player->GetCharacterMovement()->Crouch();
	}
	else
	{
		Player->GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
		Player->GetCharacterMovement()->UnCrouch();
	}
}

void ACPlayerController::Reload()
{
	bool b = true;
	b &= Player->GetDrawing() == false;
	b &= Player->GetDrawn() == true;
	b &= Player->GetSheathing() == false;
	b &= Player->GetAttacking() == false;
	b &= Player->GetCurrentBullets() < MAX_CURRENT_BULLETS;
	b &= Player->GetStoredBullets() > 0;

	if (b == false) return;

	int charge = MAX_CURRENT_BULLETS - Player->GetCurrentBullets();
	if (Player->GetStoredBullets() > charge)
	{
		Player->SetCurrentBullets(MAX_CURRENT_BULLETS);
		Player->SetStoredBullets(Player->GetStoredBullets() - charge);
	}
	else
	{
		Player->SetCurrentBullets(Player->GetCurrentBullets() + Player->GetStoredBullets());
		Player->SetStoredBullets(0);
	}

	Player->PlayAnimMontage(Player->GetReloadMontage());
}

void ACPlayerController::Roll()
{
	if (Player->GetHanging() == true) return;

	if(Player->GetCharacterMovement()->MaxWalkSpeed > WalkSpeed)
		Player->PlayAnimMontage(Player->GetRollMontage(), 1.25f);
	else
		Player->PlayAnimMontage(Player->GetRollMontage());
}

void ACPlayerController::BackStep()
{
	bool b = true;
	b &= Player->GetDrawn() == true;

	if (b == false) return;

	Player->PlayAnimMontage(Player->GetBackStepMontage());
}

void ACPlayerController::Climbing()
{
	ForwardTrace();
	HeightTrace();
	StopMoveInLedge();
}

void ACPlayerController::ForwardTrace()
{
	FVector Start = Player->GetActorLocation();
	FVector End = Player->GetActorForwardVector();
	End.X = End.X * 150.0f;
	End.Y = End.Y * 150.0f;

	End += Start;

	FHitResult OutHit;
	if (UKismetSystemLibrary::SphereTraceSingle(GetWorld(), Start, End, 20.f, ETraceTypeQuery::TraceTypeQuery1, false, actors, EDrawDebugTrace::None, OutHit, true))
	{
		WallLocation = OutHit.Location;
		WallNormal = OutHit.Normal;
	}
}

void ACPlayerController::HeightTrace()
{
	FVector Start = Player->GetActorLocation();
	Start.Z += 150.f;
	FVector Forward = Player->GetActorForwardVector();
	Forward *= 70.0f;

	Start += Forward;
	FVector End = Start;
	End.Z -= 150.f;

	FHitResult OutHit;
	if (UKismetSystemLibrary::SphereTraceSingle(GetWorld(), Start, End, 20.f, ETraceTypeQuery::TraceTypeQuery1, false, actors, EDrawDebugTrace::None, OutHit, true))
	{
		HeightLocation = OutHit.Location;
		PelvisLocation = Player->GetMesh()->GetSocketLocation(Pelvis);

		if (UKismetMathLibrary::InRange_FloatFloat(PelvisLocation.Z - HeightLocation.Z, -50.f, 0))
		{
			if (Player->GetClimbingLedge() == false)
			{
				//Player->bParkour = true;
				GrabLedge();
			}
		}
	}
}

void ACPlayerController::GrabLedge()
{
	if (Player->GetJumpingInLedge() == true) return;
	Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	Player->SetHanging(true);

	FVector RelativeLocation;
	WallNormal.X *= 22.f;
	WallNormal.Y *= 22.f;

	RelativeLocation.X = WallNormal.X + WallLocation.X;
	RelativeLocation.Y = WallNormal.Y + WallLocation.Y;
	RelativeLocation.Z = HeightLocation.Z - 120.f;

	FRotator MakeRot = UKismetMathLibrary::MakeRotFromX(WallNormal);

	FRotator RelativeRotation;
	RelativeRotation.Roll = MakeRot.Roll;
	RelativeRotation.Pitch = MakeRot.Pitch;
	RelativeRotation.Yaw = MakeRot.Yaw - 180.f;

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = Player;

	UKismetSystemLibrary::MoveComponentTo(Player->GetRootComponent(), RelativeLocation, RelativeRotation, false, false, 0.13f, false, EMoveComponentAction::Move, LatentInfo);
	Player->GetCharacterMovement()->StopMovementImmediately();
}

void ACPlayerController::ClimbLedge()
{
	if (Player->GetHanging() == true)
	{
		if (Player->GetClimbingLedge() == false)
		{
			Player->PlayAnimMontage(Player->GetClimbMontage());
			Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
			Player->SetClimbingLedge(true);
		}
	}
}

void ACPlayerController::StopMoveInLedge()
{
	if (GetInputAxisValue("MoveRight") == 0.f)
	{
		Player->SetMovingRight(false);
		Player->SetMovingLeft(false);
	}
}

void ACPlayerController::ExitLedge()
{
	if (Player->GetHanging() == false) return;
	
	Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	Player->SetHanging(false);
}

void ACPlayerController::HangingRight(float Axis)
{
	bool b = true;
	b &= Player->GetHanging() == true;
	
	if (b == false) return;
	
	if (GetInputAxisValue("MoveRight") > 0)
		Player->SetMovingRight(true);
	else if (GetInputAxisValue("MoveRight") < 0)
		Player->SetMovingLeft(true);

	if (GetInputAxisValue("MoveRight") > 0.0f)
	{
		FVector Right = Player->GetActorRightVector();
		FVector Current = Player->GetActorLocation();
		FVector Target = Current + Right * 20.0f;
		FVector NewLocation = UKismetMathLibrary::VInterpTo(Current, Target, GetWorld()->GetDeltaSeconds(), 5.0f);

		Player->SetActorLocation(NewLocation);
	}
	else if (GetInputAxisValue("MoveRight") < 0.0f)
	{
		FVector Current = Player->GetActorLocation();
		FVector Right = Player->GetActorRightVector();
		FVector Target = Current + Right * -20.0f;
		FVector NewLocation = UKismetMathLibrary::VInterpTo(Current, Target, GetWorld()->GetDeltaSeconds(), 5.0f);

		Player->SetActorLocation(NewLocation);
	}
}

void ACPlayerController::Interact()
{
	if (Player->GetSelBrazier() != NULL)
		Player->GetSelBrazier()->ToggleLight();

	if (Player->GetSwitch() && Player->GetCurrentSwitch() != NULL)
		Player->GetCurrentSwitch()->SwitchOn();
}

void ACPlayerController::ToggleTarget()
{
	if (Player->GetLockOn())
	{
		for (int i = 0; i < 10; i++)
		{
			if (Player->GetTarget(i) != NULL)
			{
				if(Player->GetTarget(i)->GetTargeted())
					Player->GetTarget(i)->SetTargeted(false);
			}
		}
		//TargetEnemy->SetTargeted(false);
		Player->GetCameraBoom()->TargetArmLength = 800.0f;
		Player->SetLockOn(false);
		CurrentTargetIndex = 0;
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			TargetEnemy = Player->GetTarget(CurrentTargetIndex);
			if (TargetEnemy == NULL)
				CurrentTargetIndex++;
			else
				break;

			if (CurrentTargetIndex >= 10)
				return;
		}

		TargetEnemy->SetTargeted(true);
		Player->GetCameraBoom()->TargetArmLength = 400.0f;
		Player->SetLockOn(true);

		//CalculateCameraRotation();
	}
}

void ACPlayerController::ChangeTarget()
{
	if (!Player->GetLockOn()) return;

	if(TargetEnemy != NULL)
		TargetEnemy->SetTargeted(false);

	CurrentTargetIndex++;

	while (CurrentTargetIndex < 10)
	{
		TargetEnemy = Player->GetTarget(CurrentTargetIndex);

		if (TargetEnemy == NULL)
		{
			CurrentTargetIndex++;

			if (CurrentTargetIndex >= 10)
			{
				CurrentTargetIndex = -1;
			}

			ChangeTarget();
		}
		else
			break;
	}

	//CalculateCameraRotation();
}

void ACPlayerController::WeaponOption()
{
	if (Player->GetMelee()) return;

	Player->ToggleWeaponOption();
}

void ACPlayerController::Pause()
{
	Player->TogglePause();
}

void ACPlayerController::Assassinate()
{
	Player->PlayAnimMontage(Player->GetThrustAttackMontage());

	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, this, &ACPlayerController::ResetCamera, 0.5f, false, 1.0f);
}

void ACPlayerController::ResetCamera()
{
	SetViewTargetWithBlend(Player, 0.5f);
}

void ACPlayerController::CalculateCameraRotation()
{
	TargetEnemy->SetTargeted(true);
	FVector cameraLoc = Player->GetCameraBoom()->GetComponentLocation();
	FVector targetLoc = TargetEnemy->GetActorLocation();

	FRotator rot = UKismetMathLibrary::FindLookAtRotation(cameraLoc, targetLoc);
	FRotator rotator = FRotator(Player->GetCameraBoom()->GetComponentRotation().Pitch, rot.Yaw, rot.Roll);
	Player->GetCameraBoom()->SetWorldRotation(rotator);
}

void ACPlayerController::WeaponUp()
{
	bool b = true;
	b &= Player->GetDrawn() == true;

	if (b == false) return;

	if (Player->GetMelee() == true)
	{
		Player->SetMelee(false);
		Player->SetRange(false);
		Player->SetMagic(true);
		Equipping();
	}
	else if (Player->GetRange() == true)
	{
		Player->SetMelee(true);
		Player->SetRange(false);
		Player->SetMagic(false);
		Equipping();
	}
	else if (Player->GetMagic() == true)
	{
		Player->SetMelee(false);
		Player->SetRange(true);
		Player->SetMagic(false);
		Equipping();
	}
}

void ACPlayerController::WeaponDown()
{
	bool b = true;
	b &= Player->GetDrawn() == true;

	if (b == false) return;

	if (Player->GetMelee() == true)
	{
		Player->SetMelee(false);
		Player->SetRange(true);
		Player->SetMagic(false);
	}
	else if (Player->GetRange() == true)
	{
		Player->SetMelee(false);
		Player->SetRange(false);
		Player->SetMagic(true);
	}
	else if (Player->GetMagic() == true)
	{
		Player->SetMelee(true);
		Player->SetRange(false);
		Player->SetMagic(false);
	}
}

void ACPlayerController::JumpToAttackMontageSection(int NewSection)
{
	if(NewSection == 1)
		Player->PlayAnimMontage(Player->GetComboAttackMontage(), 1.75f);
	else
		Player->PlayAnimMontage(Player->GetCombo2AttackMontage(), 1.5f);
}

FName ACPlayerController::GetAttackMontageSectionName(int Section)
{
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}