#include "CEnemy.h"
#include "Global.h"
#include "CEnemyWeapon.h"
#include "CAIController.h"
#include "Player/CPlayer.h"
#include "Data/CDataTable.h"
#include "CEnemyMelee.h"
#include "Animation/AnimInstance.h"
#include "Perception/PawnSensingComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/PostProcessComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "Geometry/CTargetPoint.h"

ACEnemy::ACEnemy()
{
 	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true;
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->RelativeRotation = FRotator(-10.f, -130.f, -10.f);
	CameraBoom->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(CameraBoom);

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensing");
	PawnSensing->SightRadius = 500.0f;
	PawnSensing->SetPeripheralVisionAngle(30.0f);
	PawnSensing->HearingThreshold = 1000.0f;

	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	Scene->SetupAttachment(GetMesh());

	MeleeRange = CreateDefaultSubobject<UStaticMeshComponent>("MeleeRange");
	MeleeRange->SetupAttachment(Scene);

	Outline = CreateDefaultSubobject<UPostProcessComponent>("Outline");
	Outline->SetupAttachment(Scene);

	ConstructorHelpers::FObjectFinder<UAnimMontage> down(L"/Game/Enemy/Montages/KnockDown");
	if (down.Succeeded()) KnockDownMontage = down.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> up(L"/Game/Enemy/Montages/GetUp");
	if (up.Succeeded()) GetUpMontage = up.Object;

	ConstructorHelpers::FObjectFinder<USoundBase> fire(TEXT("SoundWave'/Game/SciFiWeapDark/Sound/GrenadeLauncher/Wavs/GrenadeLauncher_Explosion03.GrenadeLauncher_Explosion03'"));
	if (fire.Succeeded()) ExplosionSound = fire.Object;

	for (int i = 0; i < 10; i++)
		TargetPoints[i] = FVector(0, 0, -100);
}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	DataTable = NewObject<UCDataTable>();
	EnemyData = DataTable->GetEnemyRow(RowName);
	Name = EnemyData->Name;
	fDamage = EnemyData->Damage;
	AttackRange = EnemyData->AttackRange;
	WalkSpeed = EnemyData->WalkSpeed;
	RunSpeed = EnemyData->MaxWalkSpeed;

	PawnSensing->SightRadius = EnemyData->SightRadius;
	GetCharacterMovement()->MaxWalkSpeed = EnemyData->WalkSpeed;
	SpawnLocation = GetActorLocation();

	AttachWeapon();

	Controller = Cast<ACAIController>(GetController());
	Controller->StartTree(EnemyData->BehaviorTree);

	Controller->GetBB()->SetValueAsObject("SelfActor", this);

	InitializeChasing();

	Player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	MaxHP = EnemyData->Health;
	CurrentHP = MaxHP;

	PawnSensing->OnSeePawn.AddDynamic(this, &ACEnemy::SeePawn);
	
}

void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	fDelta = DeltaTime;

	StartChasing();

	if (Controller->GetBB()->GetValueAsFloat("Distance") > EnemyData->EndChaseRange)
		FinishChasing();

	/*if (bDead)
	{
		if (DeathMontage != NULL)
		{
			PlayAnimMontage(DeathMontage);
		}
		Controller->GetBB()->SetValueAsBool("IsDead", bDead);
		GetCharacterMovement()->MaxWalkSpeed = 0.0f;
		bDead = false;

		FTimerHandle DeathTimer;
		GetWorld()->GetTimerManager().SetTimer(DeathTimer, this, &ACEnemy::Die, 0.3f, false, 3.0f);

		if (bTurret)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, GetActorLocation());
			Destroy();
		}
	}*/

}

void ACEnemy::SetUpNearest(ACEnemyMelee * Enemy)
{
	Controller->GetBB()->SetValueAsObject("NearestEnemy", Enemy);
}

void ACEnemy::AttachWeapon()
{
	/*FString path = EnemyData->Weapon;
	path = L"Blueprint'/Game/Enemy/" + path + "." + path + "_C'";
	UClass* type = LoadClass<ACDrill>(NULL, *path);*/

	FTransform transform = FTransform::Identity;
	FActorSpawnParameters params;
	params.Owner = this;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	if (WeaponClass == NULL) return;
	Weapon = GetWorld()->SpawnActor<ACEnemyWeapon>(WeaponClass, transform, params);

	FAttachmentTransformRules rules = FAttachmentTransformRules::SnapToTargetIncludingScale;
	rules.bWeldSimulatedBodies = false;
	Weapon->AttachToComponent(GetMesh(), rules, EnemyData->WeaponSocketName);	

	Weapon->SetDamage(EnemyData->Damage);
	Weapon->SetProjectileRange(EnemyData->AttackRange);
}

void ACEnemy::StartChasing()
{
	bool bChase = Controller->GetBB()->GetValueAsBool("IsChasing");

	if (bChase == true || RangeAttackInProgress == true)
		return;

	if (bMelee == true || bDrone == true)
		MeleeRange->SetGenerateOverlapEvents(true);
}

void ACEnemy::FinishChasing()
{
	float distance = Controller->GetPawn()->GetDistanceTo(Player);

	if (distance < EnemyData->EndChaseRange) return;

	Controller->GetBB()->SetValueAsBool("IsChasing", false);
	GetCharacterMovement()->StopMovementImmediately();

	GetWorldTimerManager().PauseTimer(StartChasingTimer);
	GetWorldTimerManager().PauseTimer(FinishChasingTimer);

	if (bMelee == true || bDrone == true)
		MeleeRange->SetGenerateOverlapEvents(false);

	Controller->GetBB()->ClearValue("Player");
}

void ACEnemy::StartAttack()
{
	FinishChasing();

	if (bAttacking == false && bKnockDown == false)
	{
		bAttacking = true;

		PlayAnimMontage(AttackMontage);
	}
}

//void ACEnemy::EndAttack()
//{
//	 Controller->GetBB()->SetValueAsBool("IsBattleStart", bAttacking);
//}

void ACEnemy::AttackEnd()
{
	bAttacking = false;
	Controller->GetBB()->SetValueAsBool("IsBattleStart", bAttacking);
}

void ACEnemy::BackStepEnd()
{
	bBackStepping = false;
}

void ACEnemy::InitializeChasing()
{
	GetWorldTimerManager().SetTimer(StartChasingTimer, this, &ACEnemy::StartChasing, 0.1f, true, 0.1f);
	GetWorldTimerManager().PauseTimer(StartChasingTimer);
	RunningTimer.Add(StartChasingTimer);

	GetWorldTimerManager().SetTimer(FinishChasingTimer, this, &ACEnemy::FinishChasing, 0.05f, true, 0.05f);
	GetWorldTimerManager().PauseTimer(FinishChasingTimer);
	RunningTimer.Add(FinishChasingTimer);
}

void ACEnemy::SeePawn(APawn * Pawn)
{
	ACPlayer* player = Cast<ACPlayer>(Pawn);

	if (player == NULL) return;

	Controller->GetBB()->SetValueAsBool("IsChasing", true);
	Controller->GetBB()->SetValueAsObject("Player", player);
}

void ACEnemy::Damage(bool bHeavy, float Damage)
{
	if (bDead) return;

	//CLog::Print(bAirDamaged);

	bDamaged = true;
	CurrentHP -= Damage;
	
	if (CurrentHP <= 0.0f)
		bDead = true;

	if (bHeavy && !bTurret && !bDrone && !bBoss)
		InAir();

	if (GetCharacterMovement()->MovementMode == EMovementMode::MOVE_None ||
		GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Falling)
		bAirDamaged = true;
	

	if (bDead)
	{
		if (DeathMontage != NULL)
		{
			PlayAnimMontage(DeathMontage);
		}
		Controller->GetBB()->SetValueAsBool("IsDead", bDead);
		GetCharacterMovement()->MaxWalkSpeed = 0.0f;

		FTimerHandle DeathTimer;
		GetWorld()->GetTimerManager().SetTimer(DeathTimer, this, &ACEnemy::Die, 0.3f, false, 3.0f);

		if (bMelee)
			Controller->GetBB()->SetValueAsObject("NearestEnemy", NULL);

		if (bTurret)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, GetActorLocation());
			Destroy();
		}
	}
}

void ACEnemy::InAir()
{
	if (GetCharacterMovement()->MovementMode == EMovementMode::MOVE_None
		|| GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Flying)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
		LaunchCharacter(FVector(0.0f, 0.0f, -1000.0f), true, true);
	}
	else
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
		LaunchCharacter(FVector(0.0f, 0.0f, 1000.0f), true, true);

		PlayAnimMontage(KnockDownMontage);

		FTimerHandle getUpHandle;
		GetWorld()->GetTimerManager().SetTimer(getUpHandle, this, &ACEnemy::GetUp, 5.0f, false, 5.0f);

		FTimerHandle airHandle;
		GetWorld()->GetTimerManager().SetTimer(airHandle, this, &ACEnemy::FixAir, 0.25f, false, 0.25f);
	}

	bKnockDown = true;
}

void ACEnemy::FixAir()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	FTimerHandle fallHandle;
	GetWorld()->GetTimerManager().SetTimer(fallHandle, this, &ACEnemy::BackToGround, 2.0f, false, 2.0f);
}

void ACEnemy::BackToGround()
{
	if(!bAirDamaged)
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
	else
	{
		bAirDamaged = false;

		FTimerHandle fallHandle;
		GetWorld()->GetTimerManager().SetTimer(fallHandle, this, &ACEnemy::BackToGround, 3.0f, false, 3.0f);
	}
}

void ACEnemy::GetUp()
{
	if (GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Walking)
	{
		if (bDead) return;

		PlayAnimMontage(GetUpMontage);
		bKnockDown = false;
	}
	else
	{
		FTimerHandle getUpHandle;
		GetWorld()->GetTimerManager().SetTimer(getUpHandle, this, &ACEnemy::GetUp, 5.0f, false, 5.0f);
	}
}

void ACEnemy::Die()
{
	if (Weapon != NULL)
		Weapon->Destroy();
	Destroy();
}



