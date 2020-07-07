#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CLightning.generated.h"

UCLASS()
class CHARACTERCPP_API ACLightning : public AActor
{
	GENERATED_BODY()
	
public:	
	ACLightning();

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
		void OnBeginOverlap
		(
			class UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromeSweep,
			const FHitResult& SweepResult
		);

public:
	class USoundBase* GetSound() { return LightningSound; }

protected:
	UPROPERTY(BlueprintReadOnly)
		class UCapsuleComponent* Capsule;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* Lightning;

private:
	class ACPlayer* Player;
	class USoundBase* LightningSound;
	
	float Damage;
};
