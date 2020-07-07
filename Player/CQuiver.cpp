#include "CQuiver.h"
#include "Components/StaticMeshComponent.h"
#include <string>

ACQuiver::ACQuiver()
{
 	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Quiver"));
	RootComponent = StaticMesh;
}

void ACQuiver::BeginPlay()
{
	Super::BeginPlay();
	
}