#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_BossMagicAttack.generated.h"

UCLASS()
class CHARACTERCPP_API UCBTTaskNode_BossMagicAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	class ACEnemyBoss* Enemy;
	class ACAIController* Controller;
	class UBlackboardComponent* BB;
};
