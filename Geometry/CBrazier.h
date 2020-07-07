#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBrazier.generated.h"

UCLASS()
class CHARACTERCPP_API ACBrazier : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBrazier();

	void ToggleLight();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	bool GetOverlapped() { return bOverlapped; }
	bool GetLightOn() { return bLightOn; }

	void SetLightOn(bool b) { bLightOn = b; }

protected:
	UPROPERTY(BlueprintReadWrite)
		bool bLightOn;

	UPROPERTY(BlueprintReadWrite)
		bool bOverlapped;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Down;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Up;

	UPROPERTY(VisibleDefaultsOnly)
		class UPointLightComponent* Light;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

private:
	class USoundBase* ToggleSound;
};
