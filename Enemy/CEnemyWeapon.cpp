#include "CEnemyWeapon.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "Player/CPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ACEnemyWeapon::ACEnemyWeapon()
{
 	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = StaticMesh;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(FName("Capsule"));
	Capsule->SetupAttachment(StaticMesh);

	bCollisionOn = true;
}

void ACEnemyWeapon::ToggleCollision()
{
	if (bCollisionOn)
		Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	else
		Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACEnemyWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ACEnemyWeapon::OnBeginOverlap);
	Owner = Cast<ACEnemy>(GetOwner());
	ToggleCollision();

	Damage = Owner->GetDamage();
}

void ACEnemyWeapon::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromeSweep, const FHitResult & SweepResult)
{
	if (OtherActor == NULL) return;
	if (OtherActor == GetOwner()) return;

	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	if (player == NULL) return;

	if (player->GetBlocking() == true)
	{
		//Owner->Damage(forward, 0.0f);

		/*if (player->GetBlockingTimer() <= 10.0f)
			player->PlayAnimMontage(player->GetThrustAttackMontage());
		else*/
			player->PlayAnimMontage(player->GetBlockReactionMontage());
	}
	else
	{
		player->Damage(DamageType::LIGHT, Damage);
		ToggleCollision();
	}
}
