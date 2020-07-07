#include "CTurretTrigger.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Components/StaticMeshComponent.h"

ACTurretTrigger::ACTurretTrigger()
{
 	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
}

void ACTurretTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACTurretTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bTriggered == false)
	{
		TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
		objectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

		TArray<AActor*> ignoreActors;
		ignoreActors.Add(this);

		FHitResult hit;
		bool bHit = UKismetSystemLibrary::LineTraceSingleForObjects
		(
			GetWorld(),
			GetActorLocation(),
			GetActorLocation() + GetActorForwardVector() * 500.0f,
			objectTypes, false, ignoreActors,
			EDrawDebugTrace::ForDuration,
			hit, true
		);

		if (bHit)
		{
			ACPlayer* player = Cast<ACPlayer>(hit.Actor);
			if (player == NULL) return;

			bTriggered = true;
		}
	}
}

