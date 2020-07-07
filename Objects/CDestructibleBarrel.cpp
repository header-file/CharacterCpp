#include "CDestructibleBarrel.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "DestructibleComponent.h"
#include "Components/BoxComponent.h"
#include "Classes/Materials/Material.h"
#include "Classes/Materials/MaterialInstanceDynamic.h"

ACDestructibleBarrel::ACDestructibleBarrel()
{
 	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UDestructibleComponent>("Mesh");
	RootComponent = Mesh;

	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	Box->SetupAttachment(Mesh);
}

void ACDestructibleBarrel::BeginPlay()
{
	Super::BeginPlay();

	bDamaged = false;
	
	//Box->OnComponentBeginOverlap.AddDynamic(this, &ACDestructibleBarrel::OnBeginOverlap);
}

void ACDestructibleBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACDestructibleBarrel::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
}

