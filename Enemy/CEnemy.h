#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CEnemy.generated.h"

UCLASS()
class CHARACTERCPP_API ACEnemy : public ACharacter
{
	GENERATED_BODY()

	friend class UCEnemyAnim;

public:
	ACEnemy();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
		float GetCurrentHP() { return CurrentHP; }

	UFUNCTION(BlueprintPure)
		float GetMaxHP() { return MaxHP; }

	UFUNCTION(BlueprintCallable)
		void SetTargetPoint(int index, FVector location) { TargetPoints[index] = location; }

	UFUNCTION(BlueprintPure)
		bool GetDamaged() { return bDamaged; }

	UFUNCTION(BlueprintPure)
		class ACAIController* GetAIController() { return Controller; }

	UFUNCTION(BlueprintPure)
		bool GetKnockDown() { return bKnockDown; }

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void Damage(bool bHeavy, float Damage);
	void InAir();
	void FixAir();
	void BackToGround();
	void GetUp();
	void Die();
	
	void StartAttack();
	//void EndAttack();

	void AttackEnd();
	void BackStepEnd();

	UFUNCTION(BlueprintPure)
		bool GetDead() { return bDead; }

	bool GetAttacking() { return bAttacking; }
	bool GetBackStepping() { return bBackStepping; }
	bool GetDash() { return bDash; }
	class ACEnemyWeapon* GetDrill() { return Weapon; }
	FVector GetTargetPoint(int i) { return TargetPoints[i]; }
	float GetRunSpeed() { return RunSpeed; }
	float GetWalkSpeed() { return WalkSpeed; }
	float GetDamage() { return fDamage; }
	float GetAttackRange() { return AttackRange; }

	class UAnimMontage* GetAttackMontage() { return AttackMontage; }
	class UAnimMontage* GetBackStepMontage() { return BackStepMontage; }
	
	class UParticleSystem* GetExplosion() { return Explosion; }
	class UParticleSystem* GetMuzzleFlash() { return MuzzleFlash; }

	class USoundBase* GetExplosionSound() { return ExplosionSound; }

	UFUNCTION(BlueprintPure)
		bool GetTargeted() { return bTargeted; }

	float GetDelta() { return fDelta; }

	void SetDead(bool b) { bDead = b;; }
	void SetAttacking(bool b) { bAttacking = b; }
	void SetBackStepping(bool b) { bBackStepping = b; }
	void SetDash(bool b) { bDash = b; }

	void SetHP(float HP) { CurrentHP = HP; }

	void SetTargeted(bool b) { bTargeted = b; }

	UFUNCTION(BlueprintCallable)
		void SetUpNearest(class ACEnemyMelee* Enemy);

private:
	void AttachWeapon();

	void StartChasing();
	void FinishChasing();

	void InitializeChasing();

	UFUNCTION()
		void SeePawn(APawn* Pawn);

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UPawnSensingComponent* PawnSensing;

	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* MeleeRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TSubclassOf<class ACEnemyWeapon > WeaponClass;

	UPROPERTY(VisibleAnywhere)
		class UParticleSystem* Explosion;

	UPROPERTY(VisibleAnywhere)
		class UParticleSystem* MuzzleFlash;

	UPROPERTY(VisibleAnywhere)
		class UPostProcessComponent* Outline;

protected:
	class UAnimMontage* AttackMontage;
	class UAnimMontage* BackStepMontage;
	class UAnimMontage* DamageMontage;
	class UAnimMontage* DeathMontage;
	class UAnimMontage* KnockDownMontage;
	class UAnimMontage* GetUpMontage;

protected:
	class ACAIController* Controller;
	class ACPlayer* Player;

	FName Name;
	FName RowName;
	const struct FEnemyData* EnemyData;

	FVector SpawnLocation;

	class ACEnemyWeapon* Weapon;

	bool bMelee;
	bool bRange;
	bool bDrone;
	bool bTurret;
	bool bBoss;

	bool bTargeted;

private:
	class UCDataTable* DataTable;
	class USoundBase* ExplosionSound;

	bool bDead;
	bool bAttacking;
	bool bBackStepping;

	bool bAirDamaged;
	bool bKnockDown;
	bool bDamaged;
	bool bDash;

	bool PlayerInAttackRange;
	bool RangeAttackInProgress;

	float WalkSpeed;
	float RunSpeed;

	FVector TargetPoints[10];

	FTimerHandle StartChasingTimer;
	FTimerHandle FinishChasingTimer;
	TArray<FTimerHandle> RunningTimer;
	TArray<float> CurrentStats;

	float MaxHP;
	float CurrentHP;

	float AttackRange;
	float fDamage;

	float fDelta = 0.0f;
};
