#include "CBTTaskNode_JumpAttack.h"
#include "Global.h"
#include "Enemy/CEnemyBoss.h"
#include "Enemy/CAIController.h"
#include "Player/CPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UCBTTaskNode_JumpAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	BB = Controller->GetBB();

	Enemy = Cast<ACEnemyBoss>(BB->GetValueAsObject("SelfActor"));
	if (Enemy->GetDash()) return EBTNodeResult::Succeeded;

	ACPlayer * player = Cast<ACPlayer>(BB->GetValueAsObject("Player"));
	CheckNullResult(player, EBTNodeResult::Failed);

	//CLog::Print(Enemy->GetCharacterMovement()->GetMovementName());

	

	return EBTNodeResult::Succeeded;
}
