#include "CArrow.h"
#include "Global.h"
#include "CPlayer.h"
#include "CBow.h"
#include "Enemy/CEnemy.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ACArrow::ACArrow()
{
 	PrimaryActorTick.bCanEverTick = true;

	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile"));
	Projectile->SetUpdatedComponent(StaticMesh);
	//Projectile->InitialSpeed = 1000.0f;
	//Projectile->MaxSpeed = 1500.0f;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Arrow"));
	RootComponent = StaticMesh;

	ConstructorHelpers::FObjectFinder<UStaticMesh> arrow(TEXT("StaticMesh'/Game/DynamicCombatSystem/Meshes/SM_ElvenArrow.SM_ElvenArrow'"));
	if (arrow.Succeeded())
		StaticMesh->SetStaticMesh(arrow.Object);

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(FName("Capsule"));
	Capsule->SetupAttachment(StaticMesh);
	Capsule->SetCapsuleHalfHeight(4.0);
	Capsule->SetCapsuleRadius(2.2);
	
	Damage = 0.25f;
}

void ACArrow::BeginPlay()
{
	Super::BeginPlay();
	
	Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ACArrow::OnBeginOverlap);
	Projectile->StopMovementImmediately();
}

void ACArrow::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromeSweep, const FHitResult & SweepResult)
{
	if (OtherActor == NULL) return;
	//if (OtherActor == Cast<ACPlayer>(GetOwner())->GetRifle()) return;
	if (OtherActor == GetOwner()) return;

	ACEnemy* enemy = Cast<ACEnemy>(OtherActor);
	if (enemy == NULL) Destroy();

	FVector forward = Cast<ACPlayer>(GetOwner())->GetMesh()->GetForwardVector();
	
	//if (enemy->GetBlocking() == true)
	//	enemy->Damage(forward, 0);
	//else
		enemy->Damage(false, Damage);
	
	Destroy();
}

void ACArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACArrow::FireInDirection(const FVector & ShootDir)
{
	Projectile->Velocity = ShootDir * Projectile->InitialSpeed;
}

