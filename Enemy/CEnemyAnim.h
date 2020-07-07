#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CEnemyAnim.generated.h"

UCLASS()
class CHARACTERCPP_API UCEnemyAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly)
		float Speed;

	UPROPERTY(BlueprintReadOnly)
		float Direction;

	UPROPERTY(BlueprintReadOnly)
		bool bInAir;

	UPROPERTY(BlueprintReadOnly)
		bool bDash;

	UPROPERTY(BlueprintReadOnly)
		bool bDead;

	UPROPERTY(BlueprintReadOnly)
		bool bAttacking;

	UPROPERTY(BlueprintReadOnly)
		bool bMeleeAttack;

	UPROPERTY(BlueprintReadOnly)
		int MeleeCount;

private:
	class ACEnemy* Enemy;
};
