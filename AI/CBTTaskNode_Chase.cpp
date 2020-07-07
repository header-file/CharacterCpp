#include "CBTTaskNode_Chase.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "Enemy/CAIController.h"
#include "Player/CPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UCBTTaskNode_Chase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	BB = Controller->GetBB();

	Enemy = Cast<ACEnemy>(BB->GetValueAsObject("SelfActor"));

	ACPlayer * player = Cast<ACPlayer>(BB->GetValueAsObject("Player"));
	CheckNullResult(player, EBTNodeResult::Failed);

	if (player->GetDead() == true) return EBTNodeResult::Failed;

	bool bBattle = BB->GetValueAsBool("IsBattleStart");
	if (bBattle == true)
		return EBTNodeResult::Succeeded;

	Enemy->GetCharacterMovement()->MaxWalkSpeed = Enemy->GetRunSpeed();

	float dist = Controller->GetPawn()->GetDistanceTo(player);
	//BB->SetValueAsFloat("Distance", dist);
	
	Controller->MoveToActor(player, Enemy->GetAttackRange() - 100.0f);

	if (dist < Enemy->GetAttackRange())
		BB->SetValueAsBool("IsBattleStart", true);

	return EBTNodeResult::Failed;
}
