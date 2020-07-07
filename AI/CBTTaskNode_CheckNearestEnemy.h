#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_CheckNearestEnemy.generated.h"

UCLASS()
class CHARACTERCPP_API UCBTTaskNode_CheckNearestEnemy : public UBTTaskNode
{
	GENERATED_BODY()

	UCBTTaskNode_CheckNearestEnemy();
	
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	class ACEnemy* Enemy;
	class ACAIController* Controller;
	class UBlackboardComponent* BB;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ACEnemyMelee> EnemyClass;
};
