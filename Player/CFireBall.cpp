#include "CFireBall.h"
#include "Global.h"
#include "CPlayer.h"
#include "Enemy/CEnemy.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ACFireBall::ACFireBall()
{
 	PrimaryActorTick.bCanEverTick = true;

	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile"));
	Projectile->SetUpdatedComponent(StaticMesh);
	Projectile->InitialSpeed = 1000.0f;
	Projectile->MaxSpeed = 1500.0f;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Arrow"));
	RootComponent = StaticMesh;

	ConstructorHelpers::FObjectFinder<UStaticMesh> sphere(TEXT("StaticMesh'/Game/DynamicCombatSystem/Meshes/SM_CollisionSphere.SM_CollisionSphere'"));
	if (sphere.Succeeded())
		StaticMesh->SetStaticMesh(sphere.Object);

	Sphere = CreateDefaultSubobject<USphereComponent>(FName("Sphere"));
	Sphere->SetupAttachment(StaticMesh);
	Sphere->SetSphereRadius(2.0f);

	FireBall = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireBall"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> fireBall(TEXT("ParticleSystem'/Game/DynamicCombatSystem/VFX/P_Fireball'"));
	if (fireBall.Succeeded()) FireBall->SetTemplate(fireBall.Object);
	FireBall->SetupAttachment(StaticMesh);

	ConstructorHelpers::FObjectFinder<UParticleSystem> fireBallHit(TEXT("ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_ThunderBallHit.P_ky_ThunderBallHit'"));
	if (fireBallHit.Succeeded()) FireHit = fireBallHit.Object;

	Damage = 20.0f;
}

void ACFireBall::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACFireBall::OnBeginOverlap);
}

void ACFireBall::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromeSweep, const FHitResult & SweepResult)
{
	if (OtherActor == NULL) return;
	if (OtherActor == GetOwner()) return;

	FTransform transform = FTransform::Identity;
	transform.SetLocation(GetActorLocation());
	transform.SetScale3D(FVector(0.5f, 0.5f, 0.5f));

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
		FireHit, transform);

	ACEnemy* enemy = Cast<ACEnemy>(OtherActor);
	if (enemy == NULL)
	{
		Destroy();
		return;
	}

	Damage *= GetActorScale3D().X;
	//FVector forward = Cast<ACPlayer>(GetOwner())->GetMesh()->GetForwardVector();
	
	//if (enemy->GetBlocking() == true)
	//	enemy->Damage(forward, 0);
	//else
		enemy->Damage(false, Damage);

	Destroy();
}

//void ACFireBall::OnBeginHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
//{
//	if (OtherActor == NULL) return;
//	if (OtherActor == GetOwner()) return;
//
//
//	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireHit, Hit.Location);
//	Destroy();
//}

void ACFireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACFireBall::FireInDirection(const FVector & ShootDir)
{
	Projectile->InitialSpeed = 1000.0f;
	Projectile->Velocity = ShootDir * Projectile->InitialSpeed;
}

