#include "CAnimNotify_BossMagic.h"
#include "Global.h"
#include "Enemy/CEnemyBoss.h"
#include "Components/SkeletalMeshComponent.h"

void UCAnimNotify_BossMagic::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACEnemyBoss* Enemy = Cast<ACEnemyBoss>(MeshComp->GetOwner());

	Enemy->SpawnWarningDecal();
}