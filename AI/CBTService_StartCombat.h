#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_StartCombat.generated.h"

UCLASS()
class CHARACTERCPP_API UCBTService_StartCombat : public UBTService
{
	GENERATED_BODY()
	
protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	class ACAIController* Controller;
	class ACEnemy* Enemy;
	class UBlackboardComponent* BB;
};
