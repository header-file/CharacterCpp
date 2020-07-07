#include "CLattice.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

ACLattice::ACLattice()
{
 	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(FName("Box"));
	RootComponent = Box;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	StaticMesh->SetupAttachment(Box);
}

void ACLattice::BeginPlay()
{
	Super::BeginPlay();
	
	Box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	StartHeight = GetActorLocation().Z;
	UpperHeight = StartHeight + 200.0f;
}

void ACLattice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bStart)
	{
		FVector loc = GetActorLocation();
		loc.Z = FMath::FInterpTo(loc.Z, UpperHeight, DeltaTime, 3.0f);

		SetActorLocation(loc);
	}
	else
	{
		FVector loc = GetActorLocation();
		loc.Z = FMath::FInterpTo(loc.Z, StartHeight, DeltaTime, 3.0f);

		SetActorLocation(loc);
	}
}

