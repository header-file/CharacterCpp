#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHltCheckDelegate);

#define MAX_CURRENT_BULLETS 30

UCLASS()
class CHARACTERCPP_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACPlayerController();

	void JumpToAttackMontageSection(int NewSection);

protected:
	void BeginPlay() override;
	void PlayerTick(float DeltaTime) override;
	void SetupInputComponent() override;

	void CameraRotation();

private:
	//WASD
	void MoveForward(float Axis);
	void MoveRight(float Axis);

	//Shift
	void Walking();
	void Running();

	//Spacebar
	void Jump();

	//Mouse Position
	void CameraPitch(float Axis);
	void CameraYaw(float Axis);

	//Mouse Wheel
	void ZoomIn();
	void ZoomOut();
	void WeaponUp();
	void WeaponDown();

	//Mouse MidClick
	void Equip();
	void Equipping();
	void Sheathing();

	//Mouse LClick
	void Attack();
	void Shoot();
	void StopVolley();
	void Spell();
	void Dispell();

	//Mouse RClick
	void Block();
	void UnBlock();
	void Aim();
	void UnAim();

	//Alt
	void ToggleSit();

	//R
	void Reload();

	//E
	void Roll();

	//Q
	void BackStep();

	//Climb
	void Climbing();
	void ForwardTrace();
	void HeightTrace();
	void GrabLedge();
	void ClimbLedge();
	void StopMoveInLedge();
	void ExitLedge();
	void HangingRight(float Axis);

	//F
	void Interact();

	//Tab
	void ToggleTarget();

	//C
	void ChangeTarget();

	//Z
	void WeaponOption();

	//P
	void Pause();

	void Assassinate();
	void ResetCamera();
	void CalculateCameraRotation();

public: 
	FOnNextAttackCheckDelegate OnNextAttackCheck; 
	FOnAttackHltCheckDelegate OnAttackHttCheck;

private:
	FName GetAttackMontageSectionName(int Section);

protected:
	UPROPERTY(BlueprintReadOnly)
		bool bSemiAuto;

private:
	UPROPERTY(EditAnywhere)
		FVector2D CameraSpeed = FVector2D(3.0f, 3.0f);

	UPROPERTY(EditAnywhere, Category = "Camera")
		float ZoomFactor = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float WalkSpeed = 250.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float RunSpeed = 600.0f;

private:
	const TArray<AActor *> actors;

private:
	class ACPlayer* Player;

	FVector2D CameraInput;
	FVector WallLocation;
	FVector WallNormal;
	FVector HeightLocation;
	FVector PelvisLocation;
	FName Pelvis = "Pelvis";

	class UParticleSystemComponent* FireHand;

	int CurrentTargetIndex = 0;
	class ACEnemy* TargetEnemy;
};
