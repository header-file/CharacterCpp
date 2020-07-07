#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_Spell.generated.h"

UCLASS()
class CHARACTERCPP_API UCAnimNotify_Spell : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
