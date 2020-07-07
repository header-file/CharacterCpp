#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_Reload.generated.h"

UCLASS()
class CHARACTERCPP_API UCBTTaskNode_Reload : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	class ACAIController* Controller;
	class ACEnemyRange* Enemy;
	class UBlackboardComponent* BB;
};
