#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CPlayerAnim.generated.h"

UCLASS()
class CHARACTERCPP_API UCPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	void NativeInitializeAnimation() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UFUNCTION(BlueprintPure)
		bool GetCanMove();

protected:
	UPROPERTY(BlueprintReadOnly)
		float Speed;

	UPROPERTY(BlueprintReadOnly)
		float Direction;
	
	UPROPERTY(BlueprintReadOnly)
		bool bDead;

	UPROPERTY(BlueprintReadOnly)
		bool bDrawn;

	UPROPERTY(BlueprintReadOnly)
		bool bDrawing;

	UPROPERTY(BlueprintReadOnly)
		bool bSheathing;

	UPROPERTY(BlueprintReadOnly)
		bool bAttacking;

	UPROPERTY(BlueprintReadOnly)
		bool bBlocking;

	UPROPERTY(BlueprintReadOnly)
		bool bAiming;

	UPROPERTY(BlueprintReadOnly)
		bool bCasting;

	UPROPERTY(BlueprintReadOnly)
		bool bSit;

	UPROPERTY(BlueprintReadOnly)
		bool bMelee;

	UPROPERTY(BlueprintReadOnly)
		bool bRange;

	UPROPERTY(BlueprintReadOnly)
		bool bMagic;

	UPROPERTY(BlueprintReadOnly)
		bool bInAir;

	UPROPERTY(BlueprintReadOnly)
		bool bHanging;

	UPROPERTY(BlueprintReadOnly)
		bool bMovingRight;

	UPROPERTY(BlueprintReadOnly)
		bool bMovingLeft;

	UPROPERTY(BlueprintReadOnly)
		bool bJumpTooHigh;

	UPROPERTY(BlueprintReadOnly)
		float Alpha;

	UPROPERTY(BlueprintReadOnly)
		FVector2D CameraInput;

	UPROPERTY(BlueprintReadOnly)
		FVector RightFootEffectorLoc;

	UPROPERTY(BlueprintReadOnly)
		FVector LeftFootEffectorLoc;


private:
	class ACPlayer* Player;

};
