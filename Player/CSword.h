#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSword.generated.h"

#define INITIALDAMAGE 5.0f

UCLASS()
class CHARACTERCPP_API ACSword : public AActor
{
	GENERATED_BODY()

public:
	ACSword();

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
	UFUNCTION(BlueprintPure)
		class UCapsuleComponent* GetCapsuleComponent() { return Capsule; }
	class UParticleSystemComponent* GetBlade() { return Blade; }
	UFUNCTION(BlueprintPure)
		class UStaticMeshComponent* GetSlicer() { return Slicer; }

	void SetAttacked(bool b) { bAttacked = b; }
	void SetHeavyAttack(bool b) { bHeavyAttack = b; }

	UFUNCTION(BlueprintCallable)
		void SetDamage(float f) { Damage = f; }

	UFUNCTION(BlueprintCallable)
		void SetAbleJump(bool b) { bAbleJump = b; }
		
	void ShowBlade();
	void HideBlade();

	void ResetDamage() { Damage = INITIALDAMAGE; }

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Handle;

	UPROPERTY(VisibleDefaultsOnly)
		class UCapsuleComponent* Capsule;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* Blade;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Slicer;

private:
	class ACPlayer* Owner;

	float Damage;

	bool bAttacked;
	bool bHeavyAttack;
	bool bAbleJump;
};
