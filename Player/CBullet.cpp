#include "CBullet.h"
#include "Global.h"
#include "CPlayer.h"
#include "CRifle.h"
#include "Enemy/CEnemy.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ACBullet::ACBullet()
{
	PrimaryActorTick.bCanEverTick = true;

	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile"));
	Projectile->SetUpdatedComponent(StaticMesh);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Bullet"));
	RootComponent = StaticMesh;

	ConstructorHelpers::FObjectFinder<UStaticMesh> bullet(TEXT("StaticMesh'/Game/SciFiWeapDark/Weapons/Darkness_AssaultRifle_Ammo.Darkness_AssaultRifle_Ammo'"));
	if (bullet.Succeeded())
		StaticMesh->SetStaticMesh(bullet.Object);

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(FName("Capsule"));
	Capsule->SetupAttachment(StaticMesh);
	Capsule->SetCapsuleHalfHeight(4.0);
	Capsule->SetCapsuleRadius(2.2);

	Damage = 0.25f;
}

void ACBullet::BeginPlay()
{
	Super::BeginPlay();
	
	Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ACBullet::OnBeginOverlap);
	Projectile->StopMovementImmediately();
}

void ACBullet::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromeSweep, const FHitResult & SweepResult)
{
	if (OtherActor == NULL) return;
	if (OtherActor == Cast<ACPlayer>(GetOwner())->GetRifle()) return;
	if (OtherActor == GetOwner()) return;

	ACEnemy* enemy = Cast<ACEnemy>(OtherActor);
	if (enemy == NULL) Destroy();

	FVector forward = Cast<ACPlayer>(GetOwner())->GetMesh()->GetForwardVector();

	/*if (enemy->GetBlocking() == true)
		enemy->Damage(forward, 0);
	else*/
	enemy->Damage(false, Damage);

	Destroy();
}

void ACBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACBullet::FireInDirection(const FVector & ShootDir)
{
	Projectile->InitialSpeed = 10000.0f;
	Projectile->Velocity = ShootDir * Projectile->InitialSpeed;
}

