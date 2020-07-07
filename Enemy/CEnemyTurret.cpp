#include "CEnemyTurret.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Enemy/CAIController.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

ACEnemyTurret::ACEnemyTurret()
{
	RowName = FName("5");

	Base = CreateDefaultSubobject<UStaticMeshComponent>("Base");
	Base->SetupAttachment(RootComponent);

	Body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	Body->SetupAttachment(Base);

	Barrel = CreateDefaultSubobject<UStaticMeshComponent>("Barrel");
	Barrel->SetupAttachment(Body);

	Muzzle = CreateDefaultSubobject<USceneComponent>("Muzzle");
	Muzzle->SetupAttachment(Barrel);

	ConstructorHelpers::FObjectFinder<UParticleSystem> flash(TEXT("ParticleSystem'/Game/Turret/Emitters/MuzzleFlash.MuzzleFlash'"));
	if (flash.Succeeded()) MuzzleFlash = flash.Object;

	ConstructorHelpers::FObjectFinder<UParticleSystem> explosion(TEXT("ParticleSystem'/Game/SciFiWeapDark/FX/Particles/P_Grenade_Explosion_Dark.P_Grenade_Explosion_Dark'"));
	if (explosion.Succeeded()) Explosion = explosion.Object;

	ConstructorHelpers::FObjectFinder<USoundBase> fire(TEXT("SoundWave'/Game/Turret/Audio/TurretFire'"));
	if (fire.Succeeded()) FireSoundBase = fire.Object;
	//FireSound = UGameplayStatics::SpawnSound2D(this, FireSoundCue);

	FireSound = CreateDefaultSubobject<UAudioComponent>("FireSound");
	FireSound->SetupAttachment(RootComponent);

	bTurret = true;
}

void ACEnemyTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTriggered)
	{
		Controller->GetBB()->SetValueAsObject("Player", Player);
	}


}
