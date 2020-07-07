#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_JumpAttack.generated.h"

UCLASS()
class CHARACTERCPP_API UCBTTaskNode_JumpAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	class ACEnemyBoss* Enemy;
	class ACAIController* Controller;
	class UBlackboardComponent* BB;
};
