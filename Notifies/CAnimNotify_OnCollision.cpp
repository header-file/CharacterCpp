#include "CAnimNotify_OnCollision.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Player/CSword.h"
#include "Enemy/CEnemyMelee.h"
#include "Enemy/CEnemyBoss.h"
#include "Enemy/CEnemyWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

void UCAnimNotify_OnCollision::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::Notify(MeshComp, Animation);

	ACPlayer* Player = Cast<ACPlayer>(MeshComp->GetOwner());
	if (Player != NULL)
	{
		Player->GetSword()->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Player->GetSword()->GetSlicer()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}

	ACEnemyMelee* EnemyMelee = Cast<ACEnemyMelee>(MeshComp->GetOwner());
	if (EnemyMelee != NULL)
		EnemyMelee->GetDrill()->GetCapsule()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	ACEnemyBoss* EnemyBoss = Cast<ACEnemyBoss>(MeshComp->GetOwner());
	if (EnemyBoss != NULL)
		EnemyBoss->OnCollision();
}
