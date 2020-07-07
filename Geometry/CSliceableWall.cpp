#include "CSliceableWall.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"

ACSliceableWall::ACSliceableWall()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMesh;

	//ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>("ProceduralMesh");
}

void ACSliceableWall::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACSliceableWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

