#include "CTargetPoint.h"
#include "Components/StaticMeshComponent.h"

ACTargetPoint::ACTargetPoint()
{
	Sphere = CreateDefaultSubobject<UStaticMeshComponent>("Sphere");
	RootComponent = Sphere;
}

void ACTargetPoint::BeginPlay()
{
	Super::BeginPlay();
	
}