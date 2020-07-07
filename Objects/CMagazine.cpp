#include "CMagazine.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Player/CPlayer.h"

ACMagazine::ACMagazine()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Magazine"));
	RootComponent = StaticMesh;

	Sphere = CreateDefaultSubobject<USphereComponent>(FName("Sphere"));
	Sphere->SetupAttachment(StaticMesh);
	Sphere->SetSphereRadius(15.0f);

	Glare = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Glare"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> glare(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Treasure/Gold_Bag/P_DeadMans_Loot.P_DeadMans_Loot'"));
	if (glare.Succeeded()) Glare->SetTemplate(glare.Object);
	Glare->SetupAttachment(StaticMesh);
}

void ACMagazine::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromeSweep, const FHitResult & SweepResult)
{
	if (OtherComp->GetFName() != FName("CollisionCylinder")) return;

	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	player->SetStoredBullets(player->GetStoredBullets() + 30);

	Destroy();
}

void ACMagazine::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACMagazine::OnBeginOverlap);
}
