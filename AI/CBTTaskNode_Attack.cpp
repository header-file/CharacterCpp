#include "CBTTaskNode_Attack.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "Enemy/CAIController.h"
#include "Player/CPlayer.h"

EBTNodeResult::Type UCBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	BB = Controller->GetBB();

	Enemy = Cast<ACEnemy>(Controller->GetPawn());

	ACPlayer * player = Cast<ACPlayer>(BB->GetValueAsObject("Player"));
	CheckNullResult(player, EBTNodeResult::Failed);

	if (Cast<ACEnemy>(BB->GetValueAsObject("NearestEnemy")) != Enemy) EBTNodeResult::Failed;

	float dist = BB->GetValueAsFloat("Distance");
	if (dist > 150.0f)
		BB->SetValueAsBool("IsBattleStart", Enemy->GetAttacking());;

	Enemy->StartAttack();

	return EBTNodeResult::Succeeded;
}