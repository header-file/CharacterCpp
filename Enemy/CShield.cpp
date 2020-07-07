#include "CShield.h"
#include "Global.h"
#include "CEnemyBoss.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

ACShield::ACShield()
{
 	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<UStaticMeshComponent>("Shield");
	RootComponent = Sphere;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	//CollisionSphere->SetupAttachment(RootComponent);
}

void ACShield::BeginPlay()
{
	Super::BeginPlay();

	MaxEnergy = CurrentEnergy = 10000.0f;
}

void ACShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentEnergy <= 0.0f)
	{
		ACEnemyBoss* boss = Cast<ACEnemyBoss>(GetOwner());
		boss->SetShield(false);
		Destroy();
	}
}

void ACShield::Damage(FVector Direction, float Damage)
{
	CurrentEnergy -= Damage;
}

