#include "CAnimNotify_BossCombo.h"
#include "Global.h"
#include "Enemy/CEnemyBoss.h"
#include "Components/SkeletalMeshComponent.h"

void UCAnimNotify_BossCombo::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACEnemyBoss* Enemy = Cast<ACEnemyBoss>(MeshComp->GetOwner());

	Enemy->ChangeCombo();
}
