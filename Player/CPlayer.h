#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

#define MAX_WEAPON_TYPE 3
#define MAX_ARROWS 10

UENUM(BlueprintType)
enum class DamageType : uint8
{
	LIGHT	UMETA(DisplayName = "Light_Attack"),
	HEAVY	UMETA(DisplayName = "Heavy_Attack")
};

UCLASS()
class CHARACTERCPP_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ACPlayer();

public:
	friend class UCPlayerAnim;

//public:
//	enum WeaponType
//	{
//		SWORD = 0,
//		BOW = 1,
//		MAGIC = 2
//	};

protected:
	virtual void BeginPlay() override;
	//void PostInitializeComponents() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
		FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/*FORCEINLINE class UCameraComponent* GetAimingCameraComponent() const { return AimingCameraComponent; }
	FORCEINLINE class USpringArmComponent* GetAimingCameraBoom() const { return AimingCameraBoom; }*/

	USceneComponent* GetRootComponent() { return RootComponent; }

	UFUNCTION(BlueprintPure)
		float GetMaxHP() { return MaxHP; }

	UFUNCTION(BlueprintPure)
		float GetCurrentHP() { return CurrentHP; }

	UFUNCTION(BlueprintPure)
		float GetMaxMP() { return MaxMP; }

	UFUNCTION(BlueprintPure)
		float GetCurrentMP() { return CurrentMP; }

	UFUNCTION(BlueprintPure)
		bool GetDead() { return bDead; }

	UFUNCTION(BlueprintPure)
		bool GetComplete() { return bComplete; }

	UFUNCTION(BlueprintPure)
		bool GetSwitch() { return bSwitch; }
	
	bool GetCanMove() { return bCanMove; }
	bool GetDrawn() { return bDrawn; }
	bool GetDrawing() { return bDrawing; }
	bool GetSheathing() { return bSheathing; }
	bool GetAttacking() { return bAttacking; }

	UFUNCTION(BlueprintPure)
		bool GetAiming() { return bAiming; }

	UFUNCTION(BlueprintPure)
		bool GetBlocking() { return bBlocking; }

	float GetBlockingTimer() { return blockingTimer; }

	UFUNCTION(BlueprintPure)
		bool GetCasting() { return bCasting; }
	bool GetSit() { return bSit; }

	UFUNCTION(BlueprintPure)
		bool GetMelee() { return bMelee; }
	UFUNCTION(BlueprintPure)
		bool GetRange() { return bRange; }
	UFUNCTION(BlueprintPure)
		bool GetMagic() { return bMagic; }

	UFUNCTION(BlueprintPure)
		bool GetSemiAuto() { return bSemiAuto; }
	UFUNCTION(BlueprintPure)
		bool GetChargeMagic() { return bChargeMagic; }

	UFUNCTION(BlueprintPure)
		bool GetPause() { return bPause; }

	bool GetJumpTooHigh() { return bJumpTooHigh; }
	bool GetHanging() { return bHanging; }
	bool GetClimbingLedge() { return bClimbingLedge; }
	bool GetJumpingInLedge() { return bJumpingInLedge; }
	bool GetMovingRight() { return bMovingRight; }
	bool GetMovingLeft() { return bMovingLeft; }

	TSubclassOf<class ACLightning> GetLightningClass() { return LightningClass; }
	//TSubclassOf<class ACBullet> GetBulletClass() { return BulletClass; }

	class UCOnCameraShake* GetCameraShake() { return CameraShake; }

	class ACBrazier* GetSelBrazier() { return SelectedBrazier; }
	class ACSwitch* GetCurrentSwitch() { return CurrentSwitch; }

	class AActor* GetAssassinateTarget() { return AssassinateTarget; }

	//bool GetCanNextCombo() { return CanNextCombo; }
	int GetCurrentCombo() { return CurrentCombo; }

	UFUNCTION(BlueprintPure)
		int GetCurrentBullets() { return CurrentBullets; }
	UFUNCTION(BlueprintPure)
		int GetStoredBullets() { return StoredBullets; }

	bool GetCombo1() { return bCombo1; }
	bool GetCombo2() { return bCombo2; }

	UFUNCTION(BlueprintPure)
		bool GetAssassin() { return bAssassin; }
	class ACEnemy* GetTarget(int Index) { return Targets[Index]; }

	bool GetDown() { return bDownAttack; }

	bool GetLockOn() { return bLockOn; }

	UFUNCTION(BlueprintPure)
		bool GetStartCheckNearest() { return bStartCheckNearest; }

	void SetMaxHP(float f) { MaxHP = f; }
	UFUNCTION(BlueprintCallable)
		void SetCurrentHP(float f) { CurrentHP = f; }
	void SetMaxMP(float f) { MaxMP = f; }
	UFUNCTION(BlueprintCallable)
		void SetCurrentMP(float f) { CurrentMP = f; }

	void SetCanMove(bool b) { bCanMove = b; }
	void SetDrawn(bool b) { bDrawn = b; }
	UFUNCTION(BlueprintCallable)
		void SetDrawing(bool b) { bDrawing = b; }
	void SetSheathing(bool b) { bSheathing = b; }
	void SetAttacking(bool b) { bAttacking = b; }
	UFUNCTION(BlueprintCallable)
		void SetBlocking(bool b) { bBlocking = b; }
	void SetBlockingTimer(float f) { blockingTimer = f; }

	UFUNCTION(BlueprintCallable)
		void SetComplete(bool b) { bComplete = b; }

	void SetAiming(bool b) { bAiming = b; }
	/*void SetBowPulling(float f) { if (BowPulling < 1) BowPulling += f; }
	void ResetBowPulling() { BowPulling = 0; }*/
	//void SetArrowIndex(int i) { ArrowIndex = i; }

	void SetCasting(bool b) { bCasting = b; }
	void SetSit(bool b) { bSit = b; }

	UFUNCTION(BlueprintCallable)
		void SetMelee(bool b) { bMelee = b; }
	void SetRange(bool b) { bRange = b; }
	void SetMagic(bool b) { bMagic = b; }

	void SetJumpTooHigh(bool b) { bJumpTooHigh = b; }
	void SetHanging(bool b) { bHanging = b; }
	void SetClimbingLedge(bool b) { bClimbingLedge = b; }
	void SetMovingRight(bool b) { bMovingRight = b; }
	void SetMovingLeft(bool b) { bMovingLeft = b; }

	void SetDamage(bool b) { bDamage = b; }

	void SetLockOn(bool b) { bLockOn = b; }

	void SetCurrentCombo(int i) { CurrentCombo = i; }
	//void SetIsComboInputOn(bool b) { IsComboInputOn = b; }

	UFUNCTION(BlueprintCallable)
		void SetCurrentBullets(int i) { CurrentBullets = i; }
	UFUNCTION(BlueprintCallable)
		void SetStoredBullets(int i) { StoredBullets = i; }

	UFUNCTION(BlueprintCallable)
		void SetSwitch(bool b) { bSwitch = b; }

	UFUNCTION(BlueprintCallable)
		void SetCurrentSwitch(class ACSwitch* CurSwitch) { CurrentSwitch = CurSwitch; }

	UFUNCTION(BlueprintCallable)
		void SetCombo1(bool b) { bCombo1 = b; }

	UFUNCTION(BlueprintCallable)
		void SetCombo2(bool b) { bCombo2 = b; }

	UFUNCTION(BlueprintCallable)
		void SetAssassin(bool b) { bAssassin = b; }

	UFUNCTION(BlueprintCallable)
		void SetAssassinateTarget(class AActor* Enemy) { AssassinateTarget = Enemy; }

	UFUNCTION(BlueprintCallable)
		void SetDown(bool b) { bDownAttack = b; }

	//IK
	void SetUpIK();
	void IKTrace(float Delta);
	float IKFootTrace(float TraceDist, FName SocketName);

	void AttackEnd();
	void ClimbEnd();

	void CheckHeight();

	void SpawnBullet();
	void SpawnLightning();
	void ThunderBallCharging();

	void Damage(DamageType Type, float Damage);

	UFUNCTION()
		void OnBeginOverlap
		(
			class UPrimitiveComponent* OverlappedComponent, 
			AActor* OtherActor, UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex, bool bFromSweep, 
			const FHitResult & SweepResult
		);

	UFUNCTION(BlueprintCallable)
		void DestroyEquipment();

	UFUNCTION(BlueprintCallable)
		void SetHeavyAttack();

	UFUNCTION(BlueprintCallable)
		void StartCheckNearest(class ACEnemyMelee* Enemy);

	UFUNCTION(BlueprintCallable)
		class ACEnemyMelee* SearchNearest();

	UFUNCTION(BlueprintCallable)
		void Shoot();

	UFUNCTION(BlueprintCallable)
		void TogglePause();

	UFUNCTION(BlueprintCallable)
		void SpawnThunderBall();

	UFUNCTION(BlueprintCallable)
		void ThrowThunderBall();

public:
	UFUNCTION(BlueprintCallable)
		class ACSword* GetSword() { return Sword; }
	class ACRifle* GetRifle() { return Rifle; }
	class ACBullet* GetBullet() { return Bullet; }
	class ACLightning* GetLightning() { return Lightning; }

public:
	void Equipped();
	void Sheathed();

	void SetToClimb();
	void SetToGround();

	void Aiming(float Delta);

	void ToggleWeaponOption();

	void EndPostEffect();

	void UpdateBeam();
	void ShakeCamera();

	UFUNCTION(BlueprintCallable)
		void SetTargets(class ACEnemy* Enemy, int Index);
	UFUNCTION(BlueprintCallable)
		void DeleteTargets(class ACEnemy* Enemy);

	UFUNCTION(BlueprintCallable)
		void SetTargetRune(class ACRuneStone* Runestone);
	UFUNCTION(BlueprintCallable)
		void DeleteTargetRune();
	/*void Aim();
	void UnAim();*/

public:
	UAnimMontage* GetComboAttackMontage() { return ComboAttackMontage; }
	UAnimMontage* GetCombo2AttackMontage() { return Combo2AttackMontage; }
	UAnimMontage* GetCombo3AttackMontage() { return Combo3AttackMontage; }
	UAnimMontage* GetDownAttackMontage() { return DownAttackMontage; }
	UAnimMontage* GetThrustAttackMontage() { return ThrustAttackMontage; }
	UAnimMontage* GetJumpAttackMontage() { return JumpAttackMontage; }
	UAnimMontage* GetBlockReactionMontage() { return BlockReactionMontage; }

	UAnimMontage* GetRollMontage() { return RollMontage; }
	UAnimMontage* GetBackStepMontage() { return BackStepMontage; }

	UAnimMontage* GetClimbMontage() { return ClimbMontage; }
	UAnimMontage* GetClimbToIdleMontage() { return ClimbToIdleMontage; }
	UAnimMontage* GetClimbRunMontage() { return ClimbRunMontage; }

	UAnimMontage* GetFireMontage() { return FireMontage; }
	UAnimMontage* GetReloadMontage() { return ReloadMontage; }

	UAnimMontage* GetSpellMontage() { return SpellMontage; }
	UAnimMontage* GetCastMontage() { return CastMontage; }
	UAnimMontage* GetBallThrowMontage() { return BallThrowMontage; }

	UAnimMontage* GetGetUpMontage() { return GetUpMontage; }

	UAnimMontage* GetWallRunRightMontage() { return WallRunRightMontage; }
	UAnimMontage* GetWallRunLeftMontage() { return WallRunLeftMontage; }

private:
	class UAnimMontage* ComboAttackMontage;
	class UAnimMontage* Combo2AttackMontage;
	class UAnimMontage* Combo3AttackMontage;
	class UAnimMontage* DownAttackMontage;
	class UAnimMontage* BlockReactionMontage;
	class UAnimMontage* ThrustAttackMontage;
	class UAnimMontage* JumpAttackMontage;
	class UAnimMontage* WarriorDamageMontage;

	class UAnimMontage* KnockDownMontage;
	class UAnimMontage* GetUpMontage;
	class UAnimMontage* DeathMontage;

	class UAnimMontage* FireMontage;
	class UAnimMontage* ReloadMontage;
	class UAnimMontage* ArcherDamageMontage;

	class UAnimMontage* SpellMontage;
	class UAnimMontage* MagicDamageMontage;
	class UAnimMontage* CastMontage;
	class UAnimMontage* BallThrowMontage;

	class UAnimMontage* RollMontage;
	class UAnimMontage* BackStepMontage;

	class UAnimMontage* ClimbMontage;
	class UAnimMontage* ClimbToIdleMontage;
	class UAnimMontage* ClimbRunMontage;

	class UAnimMontage* WallRunRightMontage;
	class UAnimMontage* WallRunLeftMontage;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(EditDefaultsOnly)
		class UPostProcessComponent* PostEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* AimingCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* AimingCameraBoom;

	UPROPERTY(VisibleAnywhere)
		class UCapsuleComponent* AssassinRange;

	UPROPERTY(VisibleAnywhere)
		class USphereComponent* TargetRange;


	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TSubclassOf<class ACSword> SwordClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TSubclassOf<class ACRifle> RifleClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TSubclassOf<class ACFireBall> ThunderBallClass;

	UPROPERTY(EditDefaultsOnly, Category = "Magic")
		TSubclassOf<class ACLightning> LightningClass;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
		TSubclassOf<class ACAimCameraActor> AimCameraClass;


	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
		bool CanNextCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
		bool IsComboInputOn;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
		int CurrentCombo = 0;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
		int MaxCombo = 2;

	UPROPERTY(VisibleAnywhere)
		class UParticleSystem* Beam;

	UPROPERTY(VisibleAnywhere)
		class UParticleSystem* Spark;

private:
	class ACSword* Sword;
	class ACRifle* Rifle;
	class ACBullet* Bullet;
	class ACLightning* Lightning;
	class ACFireBall* ThunderBall;

	class ACPlayerController* Controller;

	class UCOnCameraShake* CameraShake;

	class ACBrazier* SelectedBrazier;
	class ACSwitch* CurrentSwitch;

	class AActor* AssassinateTarget;

	class ACRuneStone* TargetRunestone;

	//State
	bool bDead;
	bool bComplete;

	bool bCanMove = true;
	bool bDrawn;
	bool bDrawing;
	bool bSheathing;
	bool bAttacking;
	bool bBlocking;
	bool bAiming;
	bool bCasting;
	bool bCanCounterAttack;
	bool bSit;
	bool bDamage;

	bool bAssassin;
	bool bDownAttack;

	bool bMelee = true;
	bool bRange;
	bool bMagic;

	bool bSemiAuto;
	bool bChargeMagic;

	bool bJumpTooHigh;
	bool bHanging;
	bool bClimbingLedge;
	bool bJumpingInLedge;
	bool bMovingRight;
	bool bMovingLeft;

	bool bSwitch;

	bool bCombo1;
	bool bCombo2;

	bool bLockOn;

	bool bPause;

	//Character Info
	float Direction;

	float MaxHP = 200.0f;
	float MaxMP = 100.0f;
	
	float CurrentHP;
	float CurrentMP;

	float blockingTimer;

	//Aiming
	FTransform NormalArm;
	float NormalArmLength;

	FTransform AimingArm;
	float AimingArmLength;

	int CurrentBullets = 30;
	int StoredBullets = 60;

	//Timer
	FTimerHandle ToneTimerHandle;
	FTimerHandle ShakeHandle;


	//Target
	class ACEnemy* Targets[10];
	class ACEnemy* LightningTargets[3];

	bool bStartCheckNearest = false;

	//IK
	float IKScale;
	float IKTraceDist;
	float IKInterpSpeed;
	float IKoffsetRightFoot;
	float IKoffsetLeftFoot;
	
	FName RIghtFootSocket;
	FName LeftFootSocket;

	//Lightning
	//FHitResult LightningHitResult;
	class UParticleSystemComponent* PSysLightning[3];
	float LightningDamage = 0.5f;
};
