#include "CLightning.h"
#include "Global.h"
#include "CPlayer.h"
#include "Enemy/CEnemy.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Effect/COnCameraShake.h"
#include "Sound/SoundBase.h"

ACLightning::ACLightning()
{
 	PrimaryActorTick.bCanEverTick = true;

	Lightning = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Lightning"));
	RootComponent = Lightning;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(FName("Capsule"));
	Capsule->SetupAttachment(Lightning);

	ConstructorHelpers::FObjectFinder<USoundBase> sound(TEXT("SoundWave'/Game/CyberHunter/Sound/WAV_LightingSparks.WAV_LightingSparks'"));
	if (sound.Succeeded()) LightningSound = sound.Object;

	Damage = 1.0f;
}

void ACLightning::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ACPlayer>(GetOwner());
	
	Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ACLightning::OnBeginOverlap);
}

void ACLightning::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromeSweep, const FHitResult & SweepResult)
{
	if (OtherActor == NULL) return;
	if (OtherActor == GetOwner()) return;

	ACEnemy* enemy = Cast<ACEnemy>(OtherActor);
	if (enemy == NULL) return;

	FVector forward = FVector(0, 0, 0);// = Cast<ACPlayer>(GetOwner())->GetMesh()->GetForwardVector();

	enemy->Damage(false, Damage);
	Player->GetCameraShake()->OnFire(Player);
}


