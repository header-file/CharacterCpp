#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CBowAnim.generated.h"

UCLASS()
class CHARACTERCPP_API UCBowAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	void NativeInitializeAnimation() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly)
		float Alpha;

private:
	class ACBow* Bow;
};
