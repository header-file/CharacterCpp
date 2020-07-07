#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_ClimbToIdle.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTERCPP_API UCAnimNotify_ClimbToIdle : public UAnimNotify
{
	GENERATED_BODY()
	
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
