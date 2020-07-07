#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CTurretTrigger.generated.h"

UCLASS()
class CHARACTERCPP_API ACTurretTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ACTurretTrigger();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
		bool GetTriggered() { return bTriggered; }

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;

	bool bTriggered;
};
