#include "CBTTaskNode_Explode.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "Enemy/CAIController.h"
#include "Player/CPlayer.h"

EBTNodeResult::Type UCBTTaskNode_Explode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	BB = Controller->GetBB();

	Enemy = Cast<ACEnemy>(Controller->GetPawn());
	if (Enemy->GetAttacking()) return EBTNodeResult::Failed;

	ACPlayer * player = Cast<ACPlayer>(BB->GetValueAsObject("Player"));
	CheckNullResult(player, EBTNodeResult::Failed);

	Enemy->PlayAnimMontage(Enemy->GetAttackMontage());
	Enemy->StartAttack();

	return EBTNodeResult::Succeeded;
}