#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CAnimNotifyState_Equipped.generated.h"

UCLASS()
class CHARACTERCPP_API UCAnimNotifyState_Equipped : public UAnimNotifyState
{
	GENERATED_BODY()

	UFUNCTION()
		void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;
	UFUNCTION()
		void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime) override;
	UFUNCTION()
		void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override;
};
