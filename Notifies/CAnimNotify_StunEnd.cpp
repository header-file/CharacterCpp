#include "CAnimNotify_StunEnd.h"
#include "Global.h"
#include "Enemy/CEnemyBoss.h"
#include "Components/SkeletalMeshComponent.h"

void UCAnimNotify_StunEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACEnemyBoss* Enemy = Cast<ACEnemyBoss>(MeshComp->GetOwner());

	Enemy->SetStun(false);
}
