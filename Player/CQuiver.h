#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CQuiver.generated.h"

UCLASS()
class CHARACTERCPP_API ACQuiver : public AActor
{
	GENERATED_BODY()
	
public:	
	ACQuiver();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* StaticMesh;	
};
