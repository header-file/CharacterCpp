#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "COnCameraShake.generated.h"

UCLASS()
class CHARACTERCPP_API UCOnCameraShake : public UObject
{
	GENERATED_BODY()
	
public:
	UCOnCameraShake();

public:
	void OnFire(class ACPlayer* Player);

private:
	TSubclassOf<class UCameraShake> CameraShakeClass;
};
