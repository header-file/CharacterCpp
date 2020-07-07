#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "CBrazierTriggerBox.generated.h"

UCLASS()
class CHARACTERCPP_API ACBrazierTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

public:
	ACBrazierTriggerBox();
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void SetUpBraziers(int index, class ACBrazier* brazier) { Braziers[index] = brazier; }
	
protected:
	UPROPERTY(BlueprintReadWrite)
		bool bComplete;

private:
	class ACBrazier* Braziers[4];
};
