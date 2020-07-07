#include "CBTTaskNode_Reload.h"
#include "Global.h"
#include "Enemy/CEnemyRange.h"
#include "Enemy/CAIController.h"
#include "Player/CPlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UCBTTaskNode_Reload::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	BB = Controller->GetBB();

	Enemy = Cast<ACEnemyRange>(Controller->GetPawn());
	//if (Enemy->GetAttacking()) return EBTNodeResult::Succeeded;
	if (Enemy->GetBackStepping()) return EBTNodeResult::Succeeded;

	ACPlayer * player = Cast<ACPlayer>(BB->GetValueAsObject("Player"));
	CheckNullResult(player, EBTNodeResult::Failed);

	if (player->GetDead() == true) return EBTNodeResult::Failed;

	if(Enemy->GetMesh()->GetAnimInstance()->Montage_IsPlaying(Enemy->GetReloadMontage()) == false)
		Enemy->PlayAnimMontage(Enemy->GetReloadMontage());

	if (BB->GetValueAsFloat("Distance") > Enemy->GetAttackRange())
		BB->SetValueAsBool("IsBattleStart", false);

	return EBTNodeResult::Succeeded;
}
