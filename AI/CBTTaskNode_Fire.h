// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_Fire.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTERCPP_API UCBTTaskNode_Fire : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	class ACAIController* Controller;
	class ACEnemyTurret* Enemy;
	class UBlackboardComponent* BB;
};
