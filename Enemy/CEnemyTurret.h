#pragma once

#include "CoreMinimal.h"
#include "Enemy/CEnemy.h"
#include "CEnemyTurret.generated.h"

UCLASS()
class CHARACTERCPP_API ACEnemyTurret : public ACEnemy
{
	GENERATED_BODY()
	
public:
	ACEnemyTurret();

	void Tick(float DeltaTime) override;

	class USceneComponent* GetMuzzle() { return Muzzle; }
	class UStaticMeshComponent* GetBody() { return Body; }
	class UAudioComponent* GetFireSound() { return FireSound; }
	class USoundBase* GetSound() { return FireSoundBase; }
	float GetCount() { return Count; }

	void SetCount(float f) { Count = f; }

public:
	UFUNCTION(BlueprintCallable)
		void SetTriggered(bool b) { bTriggered = b; }

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Base;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Body;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Barrel;

	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Muzzle;

	UPROPERTY(VisibleDefaultsOnly)
		class UAudioComponent* FireSound;

private:
	class USoundBase* FireSoundBase;

	bool bTriggered;

	float Count = 0.0f;
};
