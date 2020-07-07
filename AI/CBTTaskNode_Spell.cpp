#include "CBTTaskNode_Spell.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "Enemy/CAIController.h"
#include "Player/CPlayer.h"

EBTNodeResult::Type UCBTTaskNode_Spell::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	BB = Controller->GetBB();

	Enemy = Cast<ACEnemy>(Controller->GetPawn());
	if (Enemy->GetAttacking()) return EBTNodeResult::Failed;

	ACPlayer * player = Cast<ACPlayer>(BB->GetValueAsObject("Player"));
	CheckNullResult(player, EBTNodeResult::Failed);

	Enemy->StartAttack();
	BB->SetValueAsVector("AttackLocation", player->GetActorLocation());

	float distance = BB->GetValueAsFloat("Distance");
	if (distance < 500.0f) return EBTNodeResult::Succeeded;

	return EBTNodeResult::Failed;
}