#include "CBrazier.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/BoxComponent.h"

ACBrazier::ACBrazier()
{
 	PrimaryActorTick.bCanEverTick = true;

	Down = CreateDefaultSubobject<UStaticMeshComponent>("Down");
	RootComponent = Down;

	Up = CreateDefaultSubobject<UStaticMeshComponent>("Up");
	Up->SetupAttachment(Down);

	Light = CreateDefaultSubobject<UPointLightComponent>("Light");
	Light->SetupAttachment(Up);

	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	Box->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<USoundBase> sound(TEXT("SoundWave'/Engine/VREditor/Sounds/UI/Flashlight_Switch.Flashlight_Switch'"));
	if (sound.Succeeded()) ToggleSound = sound.Object;
}

void ACBrazier::ToggleLight()
{
	if (bLightOn)
		bLightOn = false;
	else
		bLightOn = true;

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ToggleSound, GetActorLocation());
}

void ACBrazier::BeginPlay()
{
	Super::BeginPlay();
	
	bLightOn = false;
}

void ACBrazier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bLightOn)
		Light->SetVisibility(true);
	else
		Light->SetVisibility(false);
}

