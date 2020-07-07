#include "CBTTaskNode_MoveBack.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "Enemy/CEnemyMelee.h"
#include "Enemy/CAIController.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Player/CPlayer.h"

EBTNodeResult::Type UCBTTaskNode_MoveBack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	BB = Controller->GetBB();

	Enemy = Cast<ACEnemy>(Controller->GetPawn());
	if (Enemy->GetAttacking()) return EBTNodeResult::Succeeded;
	if (Enemy->GetBackStepping()) return EBTNodeResult::Succeeded;
	if (Enemy->GetDead()) return EBTNodeResult::Succeeded;

	ACPlayer * player = Cast<ACPlayer>(BB->GetValueAsObject("Player"));
	CheckNullResult(player, EBTNodeResult::Failed);

	float distance = BB->GetValueAsFloat("Distance");
	if (distance < Enemy->GetAttackRange())
	{
		Enemy->PlayAnimMontage(Enemy->GetBackStepMontage());
		Enemy->SetBackStepping(true);
	}

	/*if (Cast<ACEnemyMelee>(Enemy) != NULL)
		BB->SetValueAsObject("NearestEnemy", NULL);*/

	return EBTNodeResult::Succeeded;
}
