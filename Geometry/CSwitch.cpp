#include "CSwitch.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

ACSwitch::ACSwitch()
{
 	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(FName("Box"));
	RootComponent = Box;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	StaticMesh->SetupAttachment(Box);
}

void ACSwitch::BeginPlay()
{
	Super::BeginPlay();
	
	Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ACSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bInteract)
	{
		FRotator rot = StaticMesh->GetComponentRotation();
		rot.Yaw = FMath::FInterpTo(rot.Yaw, 180.0f, DeltaTime, 2.0f);

		StaticMesh->SetRelativeRotation(rot.Quaternion());
	}

	if (StaticMesh->GetComponentRotation().Yaw >= 179.0f)
		bFinish = true;
}

void ACSwitch::SwitchOn()
{
	bInteract = true;
}


