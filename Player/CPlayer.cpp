#include "CPlayer.h"
#include "Global.h"
#include "Player/CPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/PostProcessComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/CSword.h"
#include "Player/CRifle.h"
#include "Player/CLightning.h"
#include "Player/CFireBall.h"
#include "Geometry/CClimber.h"
#include "Geometry/CBrazier.h"
#include "CAimCameraActor.h"
#include "Effect/COnCameraShake.h"
#include "Geometry/CClimbTriggerBox.h"
#include "Geometry/CSwitch.h"
#include "Enemy/CEnemy.h"
#include "Enemy/CEnemyMelee.h"
#include "Enemy/CAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Animation/AnimInstance.h"
#include "Geometry/CRuneStone.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	//Components
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true;
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false;

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;

	PostEffect = CreateDefaultSubobject<UPostProcessComponent>("PostEffect");
	PostEffect->SetupAttachment(RootComponent);

	AimingCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("AimingCameraBoom"));
	AimingCameraBoom->SetupAttachment(RootComponent);
	AimingCameraBoom->bAbsoluteRotation = true;
	AimingCameraBoom->TargetArmLength = 100.f;
	AimingCameraBoom->SocketOffset = FVector(0.0f, 30.0f, 70.0f);
	AimingCameraBoom->RelativeRotation = FRotator(-20.f, 0.f, 0.f);
	AimingCameraBoom->bDoCollisionTest = false;

	AssassinRange = CreateDefaultSubobject<UCapsuleComponent>("AssassinRange");
	AssassinRange->SetupAttachment(RootComponent);

	TargetRange = CreateDefaultSubobject<USphereComponent>("TargetRange");
	TargetRange->SetupAttachment(RootComponent);
	TargetRange->SetSphereRadius(320.0f);

	for (int i = 0; i < 10; i++)
		Targets[i] = NULL;
	
	//Camera Transform
	NormalArm = FTransform::Identity;
	NormalArm.SetRotation(CameraBoom->RelativeRotation.Quaternion());
	NormalArmLength = CameraBoom->TargetArmLength;

	AimingArm = FTransform::Identity;
	AimingArm.SetLocation(AimingCameraBoom->SocketOffset);
	AimingArm.SetRotation(AimingCameraBoom->GetComponentRotation().Quaternion());
	AimingArmLength = 100.0f;

	
	//Weapon
	ConstructorHelpers::FClassFinder<ACSword> sword(L"/Game/CyberHunter/BpCSword");
	if (sword.Succeeded()) SwordClass = sword.Class;

	ConstructorHelpers::FClassFinder<ACRifle> bow(L"/Game/CyberHunter/BpCRifle");
	if (bow.Succeeded()) RifleClass = bow.Class;

	/*ConstructorHelpers::FClassFinder<ACLightning> lightning(L"/Game/CyberHunter/BpCLightning");
	if (lightning.Succeeded()) LightningClass = lightning.Class;
	ConstructorHelpers::FClassFinder<ACLightning> light(L"Blueprint'/Game/CyberHunter/BpCLightning.BpCLightning_C'");
	if (light.Succeeded()) LightningClass = light.Class;*/

	ConstructorHelpers::FClassFinder<ACFireBall> thunderBall(L"/Game/CyberHunter/BpCThunderBall");
	if (thunderBall.Succeeded()) ThunderBallClass = thunderBall.Class;


	//Montage
	ConstructorHelpers::FObjectFinder<UAnimMontage> comboAttack(L"/Game/CyberHunter/Montages/Combo1");
	if (comboAttack.Succeeded()) ComboAttackMontage = comboAttack.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> combo2(L"/Game/CyberHunter/Montages/Combo2");
	if (combo2.Succeeded()) Combo2AttackMontage = combo2.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> combo3(L"/Game/CyberHunter/Montages/Combo3");
	if (combo3.Succeeded()) Combo3AttackMontage = combo3.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> down(L"/Game/CyberHunter/Montages/DownAttack");
	if (down.Succeeded()) DownAttackMontage = down.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> thrust(L"/Game/CyberHunter/Montages/CounterAttack");
	if (thrust.Succeeded()) ThrustAttackMontage = thrust.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> jump(L"/Game/CyberHunter/Montages/JumpAttack");
	if (jump.Succeeded()) JumpAttackMontage = jump.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> blockReaction(L"/Game/CyberHunter/Montages/BlockReaction");
	if (blockReaction.Succeeded()) BlockReactionMontage = blockReaction.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> reload(L"/Game/CyberHunter/Montages/Reload");
	if (reload.Succeeded()) ReloadMontage = reload.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> roll(L"/Game/CyberHunter/Montages/Roll");
	if (roll.Succeeded()) RollMontage = roll.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> backStep(L"/Game/CyberHunter/Montages/BackStep");
	if (backStep.Succeeded()) BackStepMontage = backStep.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> climb(L"/Game/CyberHunter/Montages/Climb");
	if (climb.Succeeded()) ClimbMontage = climb.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> climbToIdle(L"/Game/CyberHunter/Montages/ClimbToIdle");
	if (climbToIdle.Succeeded()) ClimbToIdleMontage = climbToIdle.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> climbRun(L"/Game/CyberHunter/Montages/ClimbRun");
	if (climbRun.Succeeded()) ClimbRunMontage = climbRun.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> shot(L"/Game/CyberHunter/Montages/Fire");
	if (shot.Succeeded()) FireMontage = shot.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> spell(L"/Game/CyberHunter/Montages/Spell");
	if (spell.Succeeded()) SpellMontage = spell.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> warriorDamage(L"/Game/CyberHunter/Montages/M_HitReaction");
	if (warriorDamage.Succeeded()) WarriorDamageMontage = warriorDamage.Object;
	
	ConstructorHelpers::FObjectFinder<UAnimMontage> archerDamage(L"/Game/CyberHunter/Montages/R_HitReaction");
	if (archerDamage.Succeeded()) ArcherDamageMontage = archerDamage.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> magicDamage(L"/Game/CyberHunter/Montages/MG_HitReaction");
	if (magicDamage.Succeeded()) MagicDamageMontage = magicDamage.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> knockDown(L"/Game/CyberHunter/Montages/KnockDown");
	if (knockDown.Succeeded()) KnockDownMontage = knockDown.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> getUp(L"/Game/CyberHunter/Montages/GetUp");
	if (getUp.Succeeded()) GetUpMontage = getUp.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> death(L"/Game/CyberHunter/Montages/Death");
	if (death.Succeeded()) DeathMontage = death.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> wallRunRight(L"/Game/CyberHunter/Montages/WallRunRight");
	if (wallRunRight.Succeeded()) WallRunRightMontage = wallRunRight.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> wallRunLeft(L"/Game/CyberHunter/Montages/WallRunLeft");
	if (wallRunLeft.Succeeded()) WallRunLeftMontage = wallRunLeft.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> cast(L"/Game/CyberHunter/Montages/Cast");
	if (cast.Succeeded()) CastMontage = cast.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> ballThrow(L"/Game/CyberHunter/Montages/BallThrow");
	if (ballThrow.Succeeded()) BallThrowMontage = ballThrow.Object;

	//Particle
	ConstructorHelpers::FObjectFinder<UParticleSystem> beam(TEXT("ParticleSystem'/Game/CyberHunter/Materials/PBeam'"));
	if(beam.Succeeded()) Beam = beam.Object;

	ConstructorHelpers::FObjectFinder<UParticleSystem> spark(TEXT("ParticleSystem'/Game/CyberHunter/Materials/PBody'"));
	if (spark.Succeeded()) Spark = spark.Object;

	//JumpSetting
	GetCharacterMovement()->JumpZVelocity = 600.0f;

	//Setting IK values
	SetUpIK();
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	FTransform transform = FTransform::Identity;
	FActorSpawnParameters params;
	params.Owner = this;

	GetController()->bFindCameraComponentWhenViewTarget = true;

	CameraShake = NewObject<UCOnCameraShake>();

	if (SwordClass == NULL) return;
	Sword = GetWorld()->SpawnActor<ACSword>(SwordClass, transform, params);
	Sword->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), FName("KnifeHolster"));

	if (RifleClass == NULL) return;
	Rifle = GetWorld()->SpawnActor<ACRifle>(RifleClass, transform, params);
	Rifle->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), FName("RifleHolster"));

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACPlayer::OnBeginOverlap);
	CurrentHP = 194;
	CurrentMP = 72;
	CurrentBullets = 12;
	StoredBullets = 120;

	PostEffect->bEnabled = false;
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckHeight();
	if (bHanging)
		bJumpTooHigh = false;

	if (!bMelee)
		Sword->HideBlade();

	if(bCasting && !bChargeMagic)
		CurrentMP -= 0.05f;
	else if (bDrawn && bMagic && CurrentMP < 100.0f)
		CurrentMP += 0.01f;

	//blockingTimer += 0.1f;

	Aiming(DeltaTime);

	//ThunderBall Charging
	if (bCasting && bChargeMagic)
		ThunderBallCharging();

	if (!bChargeMagic)
		UpdateBeam();

	//IKTrace
	IKTrace(DeltaTime);
}

void ACPlayer::SetUpIK()
{
	IKScale = GetActorScale3D().Z;
	IKTraceDist = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	IKInterpSpeed = 15.0f;
	IKoffsetRightFoot = 0.0f;
	IKoffsetLeftFoot = 0.0f;

	RIghtFootSocket = FName("RightFootIKSocket");
	LeftFootSocket = FName("LeftFootIKSocket");
}

void ACPlayer::IKTrace(float Delta)
{
	IKoffsetRightFoot = UKismetMathLibrary::FInterpTo(IKoffsetRightFoot, IKFootTrace(IKTraceDist, RIghtFootSocket), Delta, IKInterpSpeed);
	IKoffsetLeftFoot = UKismetMathLibrary::FInterpTo(IKoffsetLeftFoot, IKFootTrace(IKTraceDist, LeftFootSocket), Delta, IKInterpSpeed);

	float hipOffset = UKismetMathLibrary::Abs((IKoffsetRightFoot - IKoffsetLeftFoot));
	if (UKismetMathLibrary::NearlyEqual_FloatFloat(hipOffset, 0.0f))
		GetCapsuleComponent()->SetCapsuleHalfHeight(88.0f);
	else
		GetCapsuleComponent()->SetCapsuleHalfHeight(88.0f - hipOffset);

	//CLog::Print(GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
}

float ACPlayer::IKFootTrace(float TraceDist, FName SocketName)
{
	FVector socketLoc = GetMesh()->GetSocketLocation(SocketName);
	//float actorLocZ = GetActorLocation().Z;
	float actorLocZ = GetMesh()->GetSocketLocation(FName("spine_01")).Z;

	FVector traceStart = FVector(socketLoc.X, socketLoc.Y, actorLocZ);
	FVector traceEnd = FVector(socketLoc.X, socketLoc.Y, actorLocZ - TraceDist);

	TArray<AActor*> IgnoreActor;
	FHitResult hitResult;
	bool bHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), traceStart, traceEnd, ETraceTypeQuery::TraceTypeQuery1, true, IgnoreActor, EDrawDebugTrace::None, hitResult, true);

	if (bHit)
	{
		float IKOffset = UKismetMathLibrary::VSize(traceEnd - hitResult.Location) / IKScale;
		return IKOffset;
	}
	else
		return 0.0f;
}

void ACPlayer::AttackEnd()
{
	bAttacking = false;
	bCanMove = true;
	CurrentCombo = 0;

	if (bMelee)
	{
		Sword->ResetDamage();
		Sword->SetAttacked(false);
		Sword->SetHeavyAttack(false);
		Sword->SetAbleJump(false);
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
	}
}

void ACPlayer::ClimbEnd()
{
	bClimbingLedge = false;
	bHanging = false;
	StopAnimMontage(ClimbToIdleMontage);
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void ACPlayer::CheckHeight()
{
	if (GetCharacterMovement()->IsFalling() == true)
	{
		if (bJumpTooHigh == false)
		{
			FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
			RV_TraceParams.bTraceComplex = false;
			//RV_TraceParams.bTraceAsyncScene = true;
			RV_TraceParams.bReturnPhysicalMaterial = false;
			RV_TraceParams.AddIgnoredActor(this);

			FHitResult RV_Hit(ForceInit);

			FVector StartPosition = GetActorLocation();
			FVector EndPosition = FVector(StartPosition.X, StartPosition.Y, StartPosition.Z - 2000.0f);

			if (GetWorld()->LineTraceSingleByChannel(
				RV_Hit,
				StartPosition, EndPosition,
				ECollisionChannel::ECC_WorldDynamic,
				RV_TraceParams) == true)
			{
				if (RV_Hit.Distance >= 600.0f)
					bJumpTooHigh = true;
			}
		}
	}
}

void ACPlayer::Shoot()
{
	if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(FireMontage)) return;
	if (CurrentBullets <= 0) return;

	FVector startLocation = GetMesh()->GetSocketLocation(FName("Muzzle"));
	FVector endLocation;

	if (bAiming)
		endLocation = startLocation + GetTopDownCameraComponent()->GetForwardVector() * 3000.0f;
	else
		endLocation = startLocation + GetMesh()->GetRightVector() * 3000.0f;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);

	FHitResult result;
	bool bHit = UKismetSystemLibrary::BoxTraceSingleForObjects
	(
		GetWorld(),
		startLocation,
		endLocation,
		FVector(1, 2, 1),
		FRotator::ZeroRotator,
		ObjectTypes,
		false,
		IgnoreActors,
		EDrawDebugTrace::ForOneFrame,
		result,
		true
	);

	if (bHit)
		Rifle->OnHit(result.GetActor(), result.Location);

	PlayAnimMontage(FireMontage);
	GetCameraShake()->OnFire(this);

	CurrentBullets--;
}

void ACPlayer::SpawnBullet()
{
	FActorSpawnParameters params;
	params.Owner = this;
	FTransform transform = FTransform::Identity;
	FRotator playerRot = GetControlRotation();
	playerRot.Pitch += 90.0f;
	
	transform.SetRotation(playerRot.Quaternion());

	/*if (BulletClass == NULL) return;
	Bullet = GetWorld()->SpawnActor<ACBullet>(BulletClass, transform, params);*/
}

void ACPlayer::SpawnLightning()
{
	FVector start = GetMesh()->GetSocketLocation(FName("LightStart"));
	FTransform transform = FTransform::Identity;
	transform.SetLocation(start);

	int i = 0;
	for (; i < 8; i++)
	{
		if (IsValid(Targets[i]))
			break;
		else
			i++;
	}

	int k = 0;
	int j = i + 3;
	for (; i < j; i++)
	{
		if (IsValid(Targets[i]))
		{
			PSysLightning[i] = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Beam, transform);
			LightningTargets[k] = Targets[i];
			k++;
		}
	}

	if(TargetRunestone != NULL)
		PSysLightning[0] = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Beam, transform);

	UpdateBeam();
	
	GetWorld()->GetTimerManager().SetTimer(ShakeHandle, this, &ACPlayer::ShakeCamera, 0.2f, true, 0.3f);
}

void ACPlayer::ThunderBallCharging()
{
	if (ThunderBall == NULL) return;

	FVector scale = ThunderBall->GetActorScale3D();
	float value = 1.0f / 30.0f;

	scale += FVector(value, value, value);
	if (scale.X > 3.0f)
		scale = FVector(3.0f, 3.0f, 3.0f);
	
	ThunderBall->SetActorScale3D(scale);
}

void ACPlayer::SpawnThunderBall()
{
	FActorSpawnParameters params;
	params.Owner = this;
	FTransform transform = FTransform::Identity;

	if (ThunderBallClass == NULL) return;
	ThunderBall = GetWorld()->SpawnActor<ACFireBall>(ThunderBallClass, transform, params);
	if (ThunderBall != NULL)
	{
		ThunderBall->AttachToComponent
		(
			GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
			FName("BallSpawn")
		);
	}
}

void ACPlayer::ThrowThunderBall()
{
	if (ThunderBall == NULL) return;

	ThunderBall->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	if (bAiming)
		ThunderBall->FireInDirection(TopDownCameraComponent->GetForwardVector());
	else
		ThunderBall->FireInDirection(this->GetActorForwardVector());
}

void ACPlayer::Damage(DamageType Type, float Damage)
{
	if (bDead) return;

	bCanMove = false;

	CameraShake->OnFire(this);

	if (bBlocking == false)
		CurrentHP -= Damage / 10.0f;

	if (CurrentHP <= 0.0f)
	{
		bDead = true;
		CurrentHP = 0.0f;

		if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(WarriorDamageMontage))
			GetMesh()->GetAnimInstance()->Montage_Stop(0.1f, WarriorDamageMontage);
		else if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(ArcherDamageMontage))
			GetMesh()->GetAnimInstance()->Montage_Stop(0.1f, ArcherDamageMontage);
		else if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(MagicDamageMontage))
			GetMesh()->GetAnimInstance()->Montage_Stop(0.1f, MagicDamageMontage);

		PlayAnimMontage(DeathMontage);
	}

	if (bDamage) return;
	bDamage = true;

	if (Type == DamageType::LIGHT)
	{
		if (bMelee == true)
		{
			if (bBlocking == false && GetMesh()->GetAnimInstance()->Montage_IsPlaying(WarriorDamageMontage) == false)
				PlayAnimMontage(WarriorDamageMontage);
			else if(!GetMesh()->GetAnimInstance()->Montage_IsPlaying(BlockReactionMontage))
			{
				PlayAnimMontage(BlockReactionMontage);
				return;
			}
		}
		else if (bRange == true && GetMesh()->GetAnimInstance()->Montage_IsPlaying(ArcherDamageMontage) == false)
		{
			PlayAnimMontage(ArcherDamageMontage);
		}
		else if (bMagic == true && GetMesh()->GetAnimInstance()->Montage_IsPlaying(MagicDamageMontage) == false)
		{
			PlayAnimMontage(MagicDamageMontage);
		}
	}
	else if (Type == DamageType::HEAVY)
	{
		if (bBlocking == false && GetMesh()->GetAnimInstance()->Montage_IsPlaying(KnockDownMontage) == false)
			PlayAnimMontage(KnockDownMontage);
		else if(GetMesh()->GetAnimInstance()->Montage_IsPlaying(KnockDownMontage) == false)
		{
			PlayAnimMontage(BlockReactionMontage);
			return;
		}
	}

	PostEffect->bEnabled = true;
	GetWorld()->GetTimerManager().SetTimer(ToneTimerHandle, this, &ACPlayer::EndPostEffect, 0.1f, false, 0.5f);
}

void ACPlayer::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (GetCharacterMovement()->IsFalling())
	{
		ACClimbTriggerBox* triggerBox = Cast<ACClimbTriggerBox>(OtherActor);
		if (triggerBox == NULL) return;

		SetToClimb();
	}
	else
	{
		ACBrazier* brazier = Cast<ACBrazier>(OtherActor);
		if (brazier == NULL) return;

		SelectedBrazier = brazier;
	}
}

void ACPlayer::SetToClimb()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	bHanging = true;
}

void ACPlayer::SetToGround()
{
	bHanging = false;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void ACPlayer::Aiming(float Delta)
{
	if (bRange || bMagic)
	{
		if (bAiming)
		{
			CameraBoom->SocketOffset = FMath::VInterpTo(CameraBoom->SocketOffset, AimingArm.GetLocation(), Delta, 3.0f);
			CameraBoom->TargetArmLength = FMath::FInterpTo(CameraBoom->TargetArmLength, AimingArmLength, Delta, 3.0f);
		}
		else
		{
			CameraBoom->SocketOffset = FMath::VInterpTo(CameraBoom->SocketOffset, NormalArm.GetLocation(), GetWorld()->GetDeltaSeconds(), 3.0f);
			CameraBoom->TargetArmLength = FMath::FInterpTo(CameraBoom->TargetArmLength, NormalArmLength, GetWorld()->GetDeltaSeconds(), 3.0f);
		}
	}
}

void ACPlayer::ToggleWeaponOption()
{
	if (bRange)
	{
		if (bSemiAuto)
			bSemiAuto = false;
		else
			bSemiAuto = true;
	}
	else if (bMagic)
	{
		if (bChargeMagic)
			bChargeMagic = false;
		else
			bChargeMagic = true;
	}
}

void ACPlayer::EndPostEffect()
{
	PostEffect->bEnabled = false;
}

void ACPlayer::UpdateBeam()
{
	if (!IsValid(PSysLightning[0])) return;

	if (bCasting)
	{
		FVector start = GetMesh()->GetSocketLocation(FName("LightStart"));

		if (TargetRunestone)
		{
			PSysLightning[0]->SetBeamSourcePoint(0, start, 0);
			PSysLightning[0]->SetBeamTargetPoint(0, TargetRunestone->GetActorLocation(), 0);
		}
		/*else
		{
			PSysLightning[0]->SetBeamSourcePoint(0, start, 0);
			PSysLightning[0]->SetBeamTargetPoint(0, LightningTargets[0]->GetActorLocation(), 0);

			FTransform hitTransform = FTransform::Identity;
			hitTransform.SetLocation(LightningTargets[0]->GetActorLocation());
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Spark, hitTransform);

			LightningTargets[0]->Damage(false, LightningDamage);
		}*/
	}
	else
	{
		PSysLightning[0]->DestroyComponent();
		PSysLightning[0] = NULL;
	}

	for (int i = 1; i < 3; i++)
	{
		if (!IsValid(PSysLightning[i])) continue;

		if (bCasting)
		{
			PSysLightning[i]->SetBeamSourcePoint(0, LightningTargets[i - 1]->GetActorLocation(), 0);
			PSysLightning[i]->SetBeamTargetPoint(0, LightningTargets[i]->GetActorLocation(), 0);

			FTransform hitTransform = FTransform::Identity;
			hitTransform.SetLocation(LightningTargets[i]->GetActorLocation());
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Spark, hitTransform);

			LightningTargets[i]->Damage(false, LightningDamage);
		}
		else
		{
			PSysLightning[i]->DestroyComponent();
			PSysLightning[i] = NULL;
		}
	}
}

void ACPlayer::ShakeCamera()
{
	if(bCasting && !bChargeMagic)
		CameraShake->OnFire(this);
}

void ACPlayer::SetTargets(ACEnemy * Enemy, int Index)
{
	for (int i = 0; i < Index; i++)
	{
		if (Targets[i] == NULL)
			Targets[i] = Enemy;
	}
}

void ACPlayer::DeleteTargets(ACEnemy * Enemy)
{
	for (int i = 0; i < 10; i++)
	{
		if (Targets[i] == Enemy)
		{
			/*if (Targets[i]->GetTargeted())
			{
				CameraBoom->TargetArmLength = 400.0f;
				bLockOn = true;
				Targets[i]->SetTargeted(false);
			}*/
			
			Targets[i] = NULL;
		}
	}
}

void ACPlayer::SetTargetRune(ACRuneStone * Runestone)
{
	TargetRunestone = Runestone;
}

void ACPlayer::DeleteTargetRune()
{
	TargetRunestone = NULL;
}

void ACPlayer::DestroyEquipment()
{
	Sword->Destroy();
	Rifle->Destroy();
}

void ACPlayer::SetHeavyAttack()
{
	if (bMelee)
		Sword->SetHeavyAttack(true);
}

void ACPlayer::StartCheckNearest(ACEnemyMelee* Enemy)
{
	ACAIController* con = Enemy->GetAIController();
	UBlackboardComponent* bb = con->GetBB();
	bb->SetValueAsObject("NearestEnemy", Enemy);

	bStartCheckNearest = true;
}

ACEnemyMelee * ACPlayer::SearchNearest()
{
	ACEnemyMelee* enemies[10] = { NULL, };
	int index = 0;
	ACEnemyMelee* nearest = NULL;

	for (int i = 0; i < 10; i++)
	{
		ACEnemyMelee* melee = Cast<ACEnemyMelee>(Targets[i]);
		if (melee != NULL)
		{
			enemies[index] = melee;
			index++;
		}
	}
	nearest = enemies[0];
	if (nearest == NULL)
	{
		for (int i = 1; i < 10; i++)
		{
			nearest = enemies[i];

			if (nearest != NULL)
				break;
			else
				continue;
		}
	}
	if (nearest == NULL) return NULL;

	float nearDistance = FVector::Distance(nearest->GetActorLocation(), GetActorLocation());

	for (int i = 1; i < index; i++)
	{
		float dist = FVector::Distance(enemies[i]->GetActorLocation(), GetActorLocation());

		if (nearDistance > dist)
		{
			nearest = enemies[i];
			nearDistance = dist;
		}
	}

	return nearest;
}

void ACPlayer::TogglePause()
{
	if (bPause)
		bPause = false;
	else
		bPause = true;
}

void ACPlayer::Equipped()
{
	bDrawing = false;
	bCanMove = true;

	bDrawn = true;

	if(bMelee)
		Sword->ShowBlade();
}

void ACPlayer::Sheathed()
{
	bSheathing = false;
	bCanMove = true;

	bDrawn = false;

	if (bMelee)
	{
		Sword->HideBlade();

		Sword->AttachToComponent
		(
			GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
			FName("KnifeHolster")
		);
	}
	else if (bRange)
	{
		Rifle->AttachToComponent
		(
			GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
			FName("RifleHolster")
		);
	}
}
