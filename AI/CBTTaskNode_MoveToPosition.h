#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_MoveToPosition.generated.h"

UCLASS()
class CHARACTERCPP_API UCBTTaskNode_MoveToPosition : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UCBTTaskNode_MoveToPosition();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	class ACEnemy* Enemy;
	class ACAIController* Controller;
	class UBlackboardComponent* BB;

	int index;
};
