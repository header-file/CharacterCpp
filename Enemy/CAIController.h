#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"

UCLASS()
class CHARACTERCPP_API ACAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ACAIController();
	void StartTree(FString Path);

	class UBlackboardComponent* GetBB() { return BB; }

	float GetAngleX() { return angleX; }
	float GetAngleY() { return angleY; }

	void SetAngleX(float f) { angleX = f; }
	void SetAngleY(float f) { angleY = f; }

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class UBehaviorTreeComponent* BT;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class UBlackboardComponent* BB;

private:
	float angleX;
	float angleY;
};