#include "CEnergyCore.h"
#include "Global.h"
#include "Enemy/CEnemyBoss.h"
#include "Enemy/CShield.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

ACEnergyCore::ACEnergyCore()
{
 	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Core");
	RootComponent = StaticMesh;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	Capsule->SetupAttachment(StaticMesh);


	ConstructorHelpers::FObjectFinder<UParticleSystem> explosion(TEXT("ParticleSystem'/Game/SciFiWeapDark/FX/Particles/P_Grenade_Explosion_Dark.P_Grenade_Explosion_Dark'"));
	if (explosion.Succeeded()) Explosion = explosion.Object;
}

void ACEnergyCore::BeginPlay()
{
	Super::BeginPlay();
	
	Capsule->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ACEnergyCore::OnBeginOverlap);
}

void ACEnergyCore::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ACEnemyBoss* boss = Cast<ACEnemyBoss>(OtherActor);
	if (boss == NULL) return;

	//SpawnEmitter
	boss->GetShield()->SetCurrentEnergy(boss->GetShield()->GetCurrentEnergy() - (boss->GetShield()->GetMaxEnergy() * 0.5f));

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, GetActorTransform());

	Destroy();
}

