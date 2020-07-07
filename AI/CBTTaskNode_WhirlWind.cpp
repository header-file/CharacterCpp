#include "CBTTaskNode_WhirlWind.h"
#include "Global.h"
#include "Enemy/CEnemyBoss.h"
#include "Enemy/CAIController.h"
#include "Player/CPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UCBTTaskNode_WhirlWind::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	BB = Controller->GetBB();

	ACPlayer * player = Cast<ACPlayer>(BB->GetValueAsObject("Player"));
	CheckNullResult(player, EBTNodeResult::Failed);

	float distance = BB->GetValueAsFloat("Distance");
	if (distance <= 800.0f)
	{
		Enemy->GetCharacterMovement()->MaxWalkSpeed = Enemy->GetWalkSpeed();
		return EBTNodeResult::Succeeded;
	}

	Enemy = Cast<ACEnemyBoss>(BB->GetValueAsObject("SelfActor"));
	if (Enemy->GetAttacking()) return EBTNodeResult::Succeeded;

	Enemy->GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
	Controller->MoveToLocation(player->GetActorLocation(), 50.0f);

	Enemy->SetAttacking(true);
	Enemy->PlayAnimMontage(Enemy->GetWhirlWindMontage());

	return EBTNodeResult::Succeeded;
}