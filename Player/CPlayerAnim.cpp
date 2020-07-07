#include "CPlayerAnim.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

void UCPlayerAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Player = Cast<ACPlayer>(TryGetPawnOwner());
}

void UCPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(Player);

	Speed = Player->GetVelocity().Size();
	Direction = CalculateDirection(Player->GetVelocity(), Player->GetActorRotation());

	bDead = Player->bDead;

	bDrawn = Player->bDrawn;

	bDrawing = Player->bDrawing;
	bSheathing = Player->bSheathing;
	bAttacking = Player->bAttacking;
	bBlocking = Player->bBlocking;
	
	bAiming = Player->bAiming;
	bSit = Player->bSit;

	bCasting = Player->bCasting;
	
	bMelee = Player->bMelee;
	bRange = Player->bRange;
	bMagic = Player->bMagic;
	
	bJumpTooHigh = Player->bJumpTooHigh;
	bHanging = Player->bHanging;
	bMovingRight = Player->bMovingRight;
	bMovingLeft = Player->bMovingLeft;

	FRotator rot = Player->GetCameraBoom()->GetComponentRotation();
	CameraInput.X = rot.Yaw;
	CameraInput.Y = rot.Pitch;

	bInAir = Player->GetMovementComponent()->IsFalling();

	RightFootEffectorLoc = FVector(-Player->IKoffsetRightFoot, 0.0f, 0.0f);
	LeftFootEffectorLoc = FVector(Player->IKoffsetLeftFoot, 0.0f, 0.0f);
}

bool UCPlayerAnim::GetCanMove()
{
	Player = Cast<ACPlayer>(TryGetPawnOwner());
	if (Player == NULL) return false;

	return Player->bCanMove;
}