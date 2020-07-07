#include "CBTTaskNode_BossMeleeAttack.h"
#include "Global.h"
#include "Enemy/CEnemyBoss.h"
#include "Enemy/CAIController.h"

EBTNodeResult::Type UCBTTaskNode_BossMeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	BB = Controller->GetBB();

	Enemy = Cast<ACEnemyBoss>(Controller->GetPawn());
	if (Enemy->GetAttacking()) return EBTNodeResult::Failed;

	Enemy->SetAttacking(true);
	Enemy->PlayAnimMontage(Enemy->GetAttackMontage());

	return EBTNodeResult::Succeeded;
}