#include "CDecalActor_Warning.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Sound/SoundBase.h"

ACDecalActor_Warning::ACDecalActor_Warning()
{
	ConstructorHelpers::FObjectFinder<UParticleSystem> explosion(TEXT("ParticleSystem'/Game/SciFiWeapDark/FX/Particles/P_RocketLauncher_Explosion_Dark.P_RocketLauncher_Explosion_Dark'"));
	if (explosion.Succeeded()) Explosion = explosion.Object;

	ConstructorHelpers::FObjectFinder<USoundBase> fire(TEXT("SoundWave'/Game/SciFiWeapDark/Sound/GrenadeLauncher/Wavs/GrenadeLauncher_Explosion04.GrenadeLauncher_Explosion04'"));
	if (fire.Succeeded()) ExplosionSoundBase = fire.Object;
}

void ACDecalActor_Warning::BeginPlay()
{
	Super::BeginPlay();

	/*FScriptDelegate deleDestroy;
	deleDestroy.BindUFunction(this, ACDecalActor_Warning::OnActorDestroyed());
	this->OnDestroyed.Add(deleDestroy);*/

	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &ACDecalActor_Warning::OnActorDestroyed, 0.01f, false, 3.0f);

}

void ACDecalActor_Warning::OnActorDestroyed()
{
	FTransform transform = FTransform::Identity;
	/*FVector location = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
	location.Z -= 100.0f;*/
	transform.SetLocation(GetActorLocation());

	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSoundBase, GetActorLocation());
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, transform);
}
