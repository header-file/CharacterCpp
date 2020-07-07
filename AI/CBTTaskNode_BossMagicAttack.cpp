#include "CBTTaskNode_BossMagicAttack.h"
#include "Global.h"
#include "Enemy/CEnemyBoss.h"
#include "Enemy/CAIController.h"
#include "Player/CPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UCBTTaskNode_BossMagicAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	BB = Controller->GetBB();
	if (BB->GetValueAsFloat("HPRate") > 0.5f) return EBTNodeResult::Succeeded;

	Enemy = Cast<ACEnemyBoss>(BB->GetValueAsObject("SelfActor"));
	if (Enemy->GetAttacking()) return EBTNodeResult::Succeeded;
	if (Enemy->GetStun()) return EBTNodeResult::Failed;

	Enemy->SetAttacking(true);
	Enemy->PlayAnimMontage(Enemy->GetMagicMontage());

	return EBTNodeResult::Succeeded;
}