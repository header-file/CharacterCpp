#pragma once

#include "CoreMinimal.h"
#include "Enemy/CEnemy.h"
#include "CEnemyBoss.generated.h"

UCLASS()
class CHARACTERCPP_API ACEnemyBoss : public ACEnemy
{
	GENERATED_BODY()
	
public:
	ACEnemyBoss();

	void Tick(float DeltaTime) override;

	void ChangeCombo();
	void OnCollision();
	void OffCollision();

	void SpawnWarningDecal();

	UFUNCTION()
		void OnBeginOverlap
		(
			class UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult & SweepResult
		);

	UFUNCTION(BlueprintCallable)
		void SetTeleportPoint(int i, FVector position) { TeleportPoint[i] = position; }

	void Damage(bool bHeavy, float Damage) override;
	void ChangeColor();
	void SetDamage() { bDamage = false; }

public:
	class UAnimMontage* GetCombo2() { return Combo2Montage; }
	class UAnimMontage* GetCombo3() { return Combo3Montage; }
	class UAnimMontage* GetMagicMontage() { return MagicMontage; }
	class UAnimMontage* GetStunMontage() { return StunMontage; }
	class UAnimMontage* GetWhirlWindMontage() { return WhirlWindMontage; }
	class UAnimMontage* GetJumpMontage() { return JumpMontage; }
	class UAnimMontage* GetPreLandMontage() { return PreLandMontage; }
	class UAnimMontage* GetLandMontage() { return LandMontage; }

	class ACShield* GetShield() { return Shield; }

	void SetShield(bool b) { bShield = b; }
	void SetStun(bool b) { bStun = b; }

	bool GetStun() { return bStun; }
	FVector GetInitialPosition() { return InitialPosition; }
	FVector GetTeleportPoint(int i) { return TeleportPoint[i]; }
	
protected:
	void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* RHand;

	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* LHand;

	UPROPERTY(EditDefaultsOnly, Category = "Shield")
		TSubclassOf<class ACShield> ShieldClass;

	UPROPERTY(EditDefaultsOnly, Category = "DecalActor")
		TSubclassOf<class ACDecalActor_Warning> WarningClass;

private:
	class UAnimMontage* Combo2Montage;
	class UAnimMontage* Combo3Montage;
	class UAnimMontage* MagicMontage;
	class UAnimMontage* StunMontage;
	class UAnimMontage* WhirlWindMontage;
	class UAnimMontage* JumpMontage;
	class UAnimMontage* PreLandMontage;
	class UAnimMontage* LandMontage;

	class ACShield* Shield;

	class UMaterial* Material;
	class UMaterialInstanceDynamic* MaterialDynamic;

	FVector InitialPosition;
	FVector TeleportPoint[4];

	int Combo = 0;
	bool bShield;
	bool bStun;
	bool bDamage;
};
