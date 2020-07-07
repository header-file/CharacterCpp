#include "CBlocking.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"

ACBlocking::ACBlocking()
{
	Box = CreateDefaultSubobject<UBoxComponent>(FName("Box"));
	RootComponent = Box;

	LightningA = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle0"));
	LightningA->SetupAttachment(Box);

	LightningB = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle1"));
	LightningB->SetupAttachment(Box);

	LightningC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle2"));
	LightningC->SetupAttachment(Box);

	LightningD = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle3"));
	LightningD->SetupAttachment(Box);
}

void ACBlocking::BeginPlay()
{
	Super::BeginPlay();
	
	Box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACBlocking::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bDestroy)
		Destroy();
}

