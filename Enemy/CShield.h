#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CShield.generated.h"

UCLASS()
class CHARACTERCPP_API ACShield : public AActor
{
	GENERATED_BODY()
	
public:	
	ACShield();

protected:
	void BeginPlay() override;

public:	
	void Tick(float DeltaTime) override;

	void Damage(FVector Direction, float Damage);

	void SetCurrentEnergy(float Energy) { CurrentEnergy = Energy; }

public:
	UFUNCTION(BlueprintPure)
		float GetCurrentEnergy() { return CurrentEnergy; }

	UFUNCTION(BlueprintPure)
		float GetMaxEnergy() { return MaxEnergy; }

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Sphere;

	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* CollisionSphere;

private:
	float CurrentEnergy;
	float MaxEnergy;
};
