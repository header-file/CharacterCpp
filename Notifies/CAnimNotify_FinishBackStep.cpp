#include "CAnimNotify_FinishBackStep.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "Enemy/CEnemyMelee.h"
#include "Enemy/CAIController.h"
#include "Components/SkeletalMeshComponent.h"

void UCAnimNotify_FinishBackStep::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACEnemy* Enemy = Cast<ACEnemy>(MeshComp->GetOwner());

	if (Cast<ACEnemyMelee>(Enemy) != NULL)
		Cast<ACAIController>(Enemy->GetController())->GetBB()->SetValueAsObject("NearestEnemy", NULL);

	if (Enemy != NULL)
		Enemy->BackStepEnd();
}
