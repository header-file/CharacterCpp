#include "CStatue.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

ACStatue::ACStatue()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	Box->SetupAttachment(RootComponent);
}

void ACStatue::BeginPlay()
{
	Super::BeginPlay();

	bStart = false;
	bCharacterOn = false;
}

void ACStatue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bStart)
	{
		FRotator rot = Mesh->GetComponentRotation();
		rot.Yaw = FMath::FInterpTo(rot.Yaw, 110.0f, DeltaTime, 2.0f);

		Mesh->SetRelativeRotation(rot.Quaternion());
	}

	if (bCharacterOn)
	{
		FVector loc = Mesh->GetComponentLocation();
		loc.Z = FMath::FInterpTo(loc.Z, -900.0f, DeltaTime, 2.0f);

		Mesh->SetRelativeLocation(loc);
	}
	else
	{
		FVector loc = Mesh->GetComponentLocation();
		loc.Z = FMath::FInterpTo(loc.Z, -1300.0f, DeltaTime, 2.0f);

		Mesh->SetRelativeLocation(loc);
	}
}