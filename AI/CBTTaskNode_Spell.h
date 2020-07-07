#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_Spell.generated.h"

UCLASS()
class CHARACTERCPP_API UCBTTaskNode_Spell : public UBTTaskNode
{
	GENERATED_BODY()
	
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	class ACAIController* Controller;
	class ACEnemy* Enemy;
	class UBlackboardComponent* BB;
};
