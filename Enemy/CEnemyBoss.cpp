#include "CEnemyBoss.h"
#include "Global.h"
#include "Animation/AnimInstance.h"
#include "Classes/Materials/Material.h"
#include "Classes/Materials/MaterialInstanceDynamic.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "CDecalActor_Warning.h"
#include "Player/CPlayer.h"
#include "CShield.h"

ACEnemyBoss::ACEnemyBoss()
{
	RowName = FName("6");

	bBoss = true;

	RHand = CreateDefaultSubobject<USphereComponent>("RHand");
	RHand->SetupAttachment(GetMesh(), FName("FX_handDir_r"));
	LHand = CreateDefaultSubobject<USphereComponent>("LHand");
	LHand->SetupAttachment(GetMesh(), FName("FX_handDir_l"));

	ConstructorHelpers::FObjectFinder<UAnimMontage> attack(L"/Game/Enemy/Montages/BossCombo1");
	if (attack.Succeeded()) AttackMontage = attack.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> combo2(L"/Game/Enemy/Montages/BossCombo2");
	if (combo2.Succeeded()) Combo2Montage = combo2.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> combo3(L"/Game/Enemy/Montages/BossCombo3");
	if (combo3.Succeeded()) Combo3Montage = combo3.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> magic(L"/Game/Enemy/Montages/BossMagic");
	if (magic.Succeeded()) MagicMontage = magic.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> stun(L"/Game/Enemy/Montages/BossStun");
	if (stun.Succeeded()) StunMontage = stun.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> whirlWind(L"/Game/Enemy/Montages/BossWhirlWind");
	if (whirlWind.Succeeded()) WhirlWindMontage = whirlWind.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> jump(L"/Game/Enemy/Montages/BossJumpStart");
	if (jump.Succeeded()) JumpMontage = jump.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> preLand(L"/Game/Enemy/Montages/BossPreLand");
	if (preLand.Succeeded()) PreLandMontage = preLand.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> land(L"/Game/Enemy/Montages/BossLand");
	if (land.Succeeded()) LandMontage = land.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> death(L"/Game/Enemy/Montages/BossDeath");
	if (death.Succeeded()) DeathMontage = death.Object;


	ConstructorHelpers::FObjectFinder<UParticleSystem> explosion(TEXT("ParticleSystem'/Game/ParagonCrunch/FX/Particles/Abilities/Primary/FX/P_Crunch_Primary_Impact.P_Crunch_Primary_Impact'"));
	if (explosion.Succeeded()) Explosion = explosion.Object;


	ConstructorHelpers::FClassFinder<ACShield> shield(L"Blueprint'/Game/Enemy/Blueprints/BpCShield.BpCShield_C'");
	if (shield.Succeeded()) ShieldClass = shield.Class;

	ConstructorHelpers::FClassFinder<ACDecalActor_Warning> warning(L"Blueprint'/Game/Enemy/Blueprints/BpCDecalActor_Warning.BpCDecalActor_Warning_C'");
	if (warning.Succeeded()) WarningClass = warning.Class;

	ConstructorHelpers::FObjectFinder<UMaterial> material(L"/Game/ParagonCrunch/Characters/Heroes/Crunch/Skins/Tier_3/BlackSite/Materials/ParentMaterials/M_MASTER_BlackSite");
	if (material.Succeeded()) Material = material.Object;
}

void ACEnemyBoss::BeginPlay()
{
	Super::BeginPlay();

	RHand->OnComponentBeginOverlap.AddDynamic(this, &ACEnemyBoss::OnBeginOverlap);
	LHand->OnComponentBeginOverlap.AddDynamic(this, &ACEnemyBoss::OnBeginOverlap);

	RHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FTransform transform = FTransform::Identity;
	FActorSpawnParameters params;
	params.Owner = this;

	if (ShieldClass == NULL) return;
	Shield = GetWorld()->SpawnActor<ACShield>(ShieldClass, transform, params);
	Shield->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	bShield = true;

	MaterialDynamic = UMaterialInstanceDynamic::Create(Material, this);
	for(int i = 0; i < GetMesh()->GetNumMaterials(); i++)
		GetMesh()->SetMaterial(i, MaterialDynamic);

	InitialPosition = GetActorLocation();
}

void ACEnemyBoss::Tick(float DeltaTime)
{
	if (GetDead())
	{
		if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(MagicMontage))
			GetMesh()->GetAnimInstance()->Montage_Pause(MagicMontage);
		else if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(StunMontage))
			GetMesh()->GetAnimInstance()->Montage_Pause(StunMontage);
	}

	Super::Tick(DeltaTime);

	if (bShield)
		SetHP(GetMaxHP());
}

void ACEnemyBoss::ChangeCombo()
{
	Combo++;

	if (Combo == 1)
	{
		GetMesh()->GetAnimInstance()->Montage_Stop(0.5f, GetAttackMontage());
		PlayAnimMontage(GetCombo2());
	}
	else if (Combo == 2)
	{
		GetMesh()->GetAnimInstance()->Montage_Stop(0.5f, GetCombo2());
		PlayAnimMontage(GetCombo3());
	}
	else
		Combo = 0;
}

void ACEnemyBoss::OnCollision()
{
	RHand->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	LHand->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACEnemyBoss::OffCollision()
{
	RHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACEnemyBoss::SpawnWarningDecal()
{
	FTransform transform = FTransform::Identity;
	FVector location = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
	location.Z -= 100.0f;
	FVector rotation = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorRightVector();
	transform.SetLocation(location);
	transform.SetRotation(rotation.Rotation().Quaternion());

	FTransform trans2 = FTransform::Identity;
	float x = GetActorLocation().X + UKismetMathLibrary::RandomFloatInRange(-1.0f, 1.0f) * 1000.0f;
	float y = GetActorLocation().Y + UKismetMathLibrary::RandomFloatInRange(-1.0f, 1.0f) * 1000.0f;
	FVector loc2 = FVector(x, y, location.Z);
	trans2.SetLocation(loc2);

	FTransform trans3 = FTransform::Identity;
	x = GetActorLocation().X + UKismetMathLibrary::RandomFloatInRange(-1.0f, 1.0f) * 1000.0f;
	y = GetActorLocation().Y + UKismetMathLibrary::RandomFloatInRange(-1.0f, 1.0f) * 1000.0f;
	FVector loc3 = FVector(x, y, location.Z);
	trans3.SetLocation(loc3);

	FActorSpawnParameters params;
	params.Owner = this;

	if (WarningClass == NULL) return;
	GetWorld()->SpawnActor<ACDecalActor_Warning>(WarningClass, transform, params);
	GetWorld()->SpawnActor<ACDecalActor_Warning>(WarningClass, trans2, params);
	GetWorld()->SpawnActor<ACDecalActor_Warning>(WarningClass, trans3, params);
}

void ACEnemyBoss::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == this) return;
	
	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	if (player == NULL) return;
	player->Damage(DamageType::LIGHT, GetDamage());

	/*FTransform transform;
	transform.SetLocation(SweepResult.ImpactPoint);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, transform);*/
}

void ACEnemyBoss::Damage(bool bHeavy, float Damage)
{
	Super::Damage(bHeavy, Damage);

	bDamage = true;

	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, this, &ACEnemyBoss::ChangeColor, 0.1f, true, 0.0f);

	FTimerHandle damageHandle;
	GetWorld()->GetTimerManager().SetTimer(damageHandle, this, &ACEnemyBoss::SetDamage, 0.5f, false, 0.2f);
}

void ACEnemyBoss::ChangeColor()
{
	if (bDamage)
	{
		FLinearColor color;
		color.R = 1.0f;
		color.G = 0.0f;
		color.B = 0.0f;
		color.A = 1.0f;

		MaterialDynamic->SetVectorParameterValue("Color", color);
	}
	else
	{
		FLinearColor color;
		color.R = 1.0f;
		color.G = 1.0f;
		color.B = 1.0f;
		color.A = 1.0f;

		MaterialDynamic->SetVectorParameterValue("Color", color);
	}
}
