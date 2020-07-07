#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CTargetPoint.generated.h"

UCLASS()
class CHARACTERCPP_API ACTargetPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	ACTargetPoint();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Sphere;
};
