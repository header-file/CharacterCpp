#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_RotateTurret.generated.h"


UCLASS()
class CHARACTERCPP_API UCBTTaskNode_RotateTurret : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	class ACAIController* Controller;
	class ACEnemyTurret* Enemy;
	class UBlackboardComponent* BB;
};
