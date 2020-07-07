#include "CSword.h"
#include "Global.h"
#include "CPlayer.h"
#include "Enemy/CEnemy.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Effect/COnCameraShake.h"

ACSword::ACSword()
{
	PrimaryActorTick.bCanEverTick = true;

	Blade = CreateDefaultSubobject<UParticleSystemComponent>("Blade");
	Blade->SetupAttachment(RootComponent);

	Handle = CreateDefaultSubobject<UStaticMeshComponent>(FName("Handle"));
	Handle->SetupAttachment(RootComponent);

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(FName("Capsule"));
	Capsule->SetupAttachment(Blade);
	Capsule->SetCapsuleHalfHeight(220);
	Capsule->SetCapsuleRadius(22);

	Slicer = CreateDefaultSubobject<UStaticMeshComponent>("Slicer");
	Slicer->SetupAttachment(RootComponent);

	Damage = INITIALDAMAGE;
}

void ACSword::BeginPlay()
{
	Super::BeginPlay();

	Slicer->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ACSword::OnBeginOverlap);
	Owner = Cast<ACPlayer>(GetOwner());

	Blade->SetActive(false);
}

void ACSword::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromeSweep, const FHitResult & SweepResult)
{
	if (OtherActor == NULL) return;
	if (OtherActor == GetOwner()) return;
	if (bAttacked) return;

	ACEnemy* enemy = Cast<ACEnemy>(OtherActor);
	if (enemy == NULL) return;

	Owner->GetCameraShake()->OnFire(Owner);

	enemy->Damage(bHeavyAttack, Damage);
	bAttacked = true;

	if (bAbleJump)
		Owner->Jump();
}

void ACSword::ShowBlade()
{
	Blade->SetActive(true);
	Blade->SetVisibility(true);
}

void ACSword::HideBlade()
{
	Blade->SetVisibility(false);
	Blade->SetActive(false);
}
