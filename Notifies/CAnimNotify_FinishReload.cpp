#include "CAnimNotify_FinishReload.h"
#include "Global.h"
#include "Enemy/CEnemyRange.h"
#include "Components/SkeletalMeshComponent.h"

void UCAnimNotify_FinishReload::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACEnemyRange* Enemy = Cast<ACEnemyRange>(MeshComp->GetOwner());

	if (Enemy != NULL)
		Enemy->FinishReload();
}