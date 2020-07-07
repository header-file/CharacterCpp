#include "CEnemyAnim.h"
#include "Global.h"
#include "CEnemy.h"
#include "CEnemyMelee.h"
#include "CAIController.h"
#include "Player/CPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCEnemyAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Enemy = Cast<ACEnemy>(TryGetPawnOwner());
}

void UCEnemyAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(Enemy)

	if (Enemy == NULL) return;

	ACAIController* aiCon = Cast<ACAIController>(Enemy->GetController());
	if (aiCon != NULL)
	{
		ACPlayer* player = Cast<ACPlayer>(aiCon->GetBB()->GetValueAsObject("Player"));

		if (Cast<ACEnemyMelee>(Enemy) != NULL && player != NULL)
		{
			FVector selfLoc = Enemy->GetActorLocation();
			FVector targetLoc = player->GetActorLocation();

			FRotator tempRot = UKismetMathLibrary::FindLookAtRotation(selfLoc, targetLoc);
			FRotator rot = FRotator(Enemy->GetActorRotation().Pitch, tempRot.Yaw, Enemy->GetActorRotation().Roll);
			Enemy->SetActorRotation(rot);
		}
	}

	Speed = Enemy->GetVelocity().Size();
	Direction = CalculateDirection(Enemy->GetVelocity(), Enemy->GetActorRotation());
	bInAir = Enemy->GetCharacterMovement()->IsFalling();
	bDash = Enemy->bDash;

	bDead = Enemy->bDead;
	bAttacking = Enemy->bAttacking;

	if (Enemy->IsA<ACEnemyMelee>())		// IsA : 상속 관계 확인
	{
		bMeleeAttack = Enemy->PlayerInAttackRange;
		MeleeCount = 0;
	}
}
