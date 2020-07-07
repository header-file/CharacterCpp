#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_RangeAttack.generated.h"


UCLASS()
class CHARACTERCPP_API UCBTTaskNode_RangeAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	class ACAIController* Controller;
	class ACEnemy* Enemy;
	class UBlackboardComponent* BB;
};
