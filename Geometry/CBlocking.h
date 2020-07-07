#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBlocking.generated.h"

UCLASS()
class CHARACTERCPP_API ACBlocking : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBlocking();

protected:
	virtual void BeginPlay() override;

public:
	void Tick(float DeltaTime);

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* LightningA;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* LightningB;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* LightningC;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* LightningD;

protected:
	UPROPERTY(BlueprintReadWrite)
		bool bDestroy;
};
