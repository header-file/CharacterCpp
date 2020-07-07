#include "CMedKit.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Player/CPlayer.h"

ACMedKit::ACMedKit()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("MedKit"));
	RootComponent = StaticMesh;

	Sphere = CreateDefaultSubobject<USphereComponent>(FName("Sphere"));
	Sphere->SetupAttachment(StaticMesh);
	Sphere->SetSphereRadius(70.0f);

	Glare = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Glare"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> glare(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Mobile/combat/Charge_Red.Charge_Red'"));
	if (glare.Succeeded()) Glare->SetTemplate(glare.Object);
	Glare->SetupAttachment(StaticMesh);

	HealRatio = 0.0f;
}

void ACMedKit::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACMedKit::OnBeginOverlap);
}

void ACMedKit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator rot = StaticMesh->GetComponentRotation();
	rot.Yaw += 5.0f;
	StaticMesh->SetRelativeRotation(rot.Quaternion());
}

void ACMedKit::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromeSweep, const FHitResult & SweepResult)
{
	if (OtherComp->GetFName() != FName("CollisionCylinder")) return;

	ACPlayer* player = Cast<ACPlayer>(OtherActor);

	float maxHP = player->GetMaxHP();
	player->SetCurrentHP(player->GetCurrentHP() + maxHP * HealRatio);

	if (player->GetCurrentHP() > maxHP)
		player->SetCurrentHP(maxHP);

	Destroy();
}

