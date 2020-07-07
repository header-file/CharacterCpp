#include "CRifle.h"
#include "Global.h"
#include "CPlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include "Enemy/CEnemy.h"

ACRifle::ACRifle()
{
 	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Bow"));
	RootComponent = SkeletalMesh;

	ConstructorHelpers::FObjectFinder<UParticleSystem> impact(TEXT("ParticleSystem'/Game/SciFiWeapDark/FX/Particles/P_Impact_Metal_Medium_Dark.P_Impact_Metal_Medium_Dark'"));
	if (impact.Succeeded()) Impact = impact.Object;
}

void ACRifle::BeginPlay()
{
	Super::BeginPlay();
	
	Damage = 10.0f;
}

void ACRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACRifle::OnHit(AActor * OtherActor, FVector Location)
{
	if (OtherActor == NULL) return;
	if (OtherActor == Cast<ACPlayer>(GetOwner())->GetRifle()) return;
	if (OtherActor == GetOwner()) return;

	ACEnemy* enemy = Cast<ACEnemy>(OtherActor);
	if (enemy == NULL) return;

	FVector forward = Cast<ACPlayer>(GetOwner())->GetMesh()->GetForwardVector();

	enemy->Damage(false, Damage);

	FTransform transform = FTransform::Identity;
	transform.SetLocation(Location);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Impact, transform);
}

