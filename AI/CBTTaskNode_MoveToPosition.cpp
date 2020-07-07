#include "CBTTaskNode_MoveToPosition.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "Enemy/CAIController.h"
#include "Geometry/CTargetPoint.h"
#include "GameFramework/CharacterMovementComponent.h"

UCBTTaskNode_MoveToPosition::UCBTTaskNode_MoveToPosition()
{
	index = 0;
}

EBTNodeResult::Type UCBTTaskNode_MoveToPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	BB = Controller->GetBB();

	APawn* pawn = Controller->GetPawn();
	Enemy = Cast<ACEnemy>(Controller->GetPawn());

	if (BB->GetValueAsObject("Player") != NULL)
		return EBTNodeResult::Succeeded;

	if(Enemy->GetTargetPoint(0) == FVector(0, 0, -100)) return EBTNodeResult::Failed;

	FVector target = Enemy->GetTargetPoint(index);

	Enemy->GetCharacterMovement()->MaxWalkSpeed = Enemy->GetWalkSpeed();

	FPathFollowingResult result = Controller->MoveToLocation(target, 10.0f);
	if (result.Code == EPathFollowingResult::Success)
	{
		FVector next = Enemy->GetTargetPoint(index + 1);
		if (next.X != 0.0f && next.Y != 0.0f && next.Z != -100.0f)
			index++;
		else
			index = 0;
	}

	return EBTNodeResult::Failed;
}