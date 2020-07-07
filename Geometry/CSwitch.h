#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSwitch.generated.h"

UCLASS()
class CHARACTERCPP_API ACSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSwitch();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void SwitchOn();

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* StaticMesh;

protected:
	UPROPERTY(BlueprintReadOnly)
		bool bFinish;

private:
	bool bInteract;
};
