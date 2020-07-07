#include "CAnimNotify_OffCollision.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Player/CSword.h"
#include "Enemy/CEnemyMelee.h"
#include "Enemy/CEnemyBoss.h"
#include "Enemy/CEnemyWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

void UCAnimNotify_OffCollision::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::Notify(MeshComp, Animation);

	ACPlayer* Player = Cast<ACPlayer>(MeshComp->GetOwner());
	if (Player != NULL)
	{
		Player->GetSword()->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Player->GetSword()->GetSlicer()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	ACEnemyMelee* EnemyMelee = Cast<ACEnemyMelee>(MeshComp->GetOwner());
	if (EnemyMelee != NULL)
		EnemyMelee->GetDrill()->GetCapsule()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	ACEnemyBoss* EnemyBoss = Cast<ACEnemyBoss>(MeshComp->GetOwner());
	if (EnemyBoss != NULL)
		EnemyBoss->OffCollision();
}
