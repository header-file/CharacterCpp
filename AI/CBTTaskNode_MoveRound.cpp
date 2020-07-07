#include "CBTTaskNode_MoveRound.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "Player/CPlayer.h"
#include "Enemy/CAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UCBTTaskNode_MoveRound::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	BB = Controller->GetBB();

	APawn* pawn = Controller->GetPawn();
	Enemy = Cast<ACEnemy>(Controller->GetPawn());
	if (Enemy->GetDead()) return EBTNodeResult::Failed;

	ACPlayer* player = Cast<ACPlayer>(BB->GetValueAsObject("Player"));

	if (BB->GetValueAsObject("NearestEnemy") == Enemy)
	{
		Enemy->GetCharacterMovement()->MaxWalkSpeed = Enemy->GetRunSpeed();
		return EBTNodeResult::Failed;
	}
	
	float distance = FVector::Distance(Enemy->GetActorLocation(), player->GetActorLocation());
	FVector nowLocation = Enemy->GetActorLocation();
	FVector playerLocation = player->GetActorLocation();

	if (Enemy->GetAttacking()) return EBTNodeResult::Succeeded;
	if (Enemy->GetKnockDown()) return EBTNodeResult::Succeeded;
	
	Enemy->GetCharacterMovement()->MaxWalkSpeed = Enemy->GetWalkSpeed();
	//float angle = UKismetMathLibrary::Atan2(nowLocation.Y - playerLocation.Y, nowLocation.X - playerLocation.X);
	
	//nowLocation = FMath::VInterpTo(nowLocation, FVector(playerLocation.X + 500.0f * sinf(angle + 0.5f), nowLocation.Y + 500.0f * cosf(angle + 0.5f), nowLocation.Z), Enemy->GetDelta(), 1.0f);
	//Enemy->SetActorLocation(nowLocation);
	FVector targetLoc = FVector(playerLocation.X + 500.0f * cosf(Controller->GetAngleX()), playerLocation.Y + 500.0f * sinf(Controller->GetAngleX()), nowLocation.Z);
	FPathFollowingResult result = Controller->MoveToLocation(targetLoc, 100.0f);
	if (result.Code == EPathFollowingResult::Success/* || result.Code == EPathFollowingResult::Blocked*/)
	{
		Controller->SetAngleX(UKismetMathLibrary::RandomFloatInRange(-UKismetMathLibrary::GetPI(), UKismetMathLibrary::GetPI()));
		Controller->SetAngleY(UKismetMathLibrary::RandomFloatInRange(-UKismetMathLibrary::GetPI(), UKismetMathLibrary::GetPI()));
	}

	/*if (BB->GetValueAsFloat("Distance") >= Enemy->GetAttackRange())
		BB->SetValueAsBool("IsBattleStart", false);*/
	
	return EBTNodeResult::Succeeded;
}