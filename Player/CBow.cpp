#include "CBow.h"
#include "Global.h"
#include "CPlayer.h"
#include "Components/SkeletalMeshComponent.h"

ACBow::ACBow()
{
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Bow"));
	RootComponent = SkeletalMesh;
}

void ACBow::BeginPlay()
{
	Super::BeginPlay();
	

}

void ACBow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ACPlayer* player = Cast<ACPlayer>(GetOwner());

	//Alpha = player->GetBowPulling();
}

