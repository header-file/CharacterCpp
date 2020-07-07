#include "CBTTaskNode_BossTeleport.h"
#include "Global.h"
#include "Enemy/CEnemyBoss.h"
#include "Player/CPlayer.h"
#include "Enemy/CAIController.h"

EBTNodeResult::Type UCBTTaskNode_BossTeleport::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	BB = Controller->GetBB();
	if (BB->GetValueAsFloat("HPRate") > 0.5f) return EBTNodeResult::Succeeded;

	Enemy = Cast<ACEnemyBoss>(Controller->GetPawn());
	if (Enemy->GetAttacking()) return EBTNodeResult::Failed;

	/*FVector position = Enemy->GetInitialPosition();
	float x = position.X + UKismetMathLibrary::RandomFloatInRange(-1.0f, 1.0f) * 100.0f;
	float y = position.Y + UKismetMathLibrary::RandomFloatInRange(-1.0f, 1.0f) * 100.0f;
	float z = position.Z + 100.0f;

	Enemy->SetActorLocation(FVector(x, y, z));*/

	int index = UKismetMathLibrary::RandomIntegerInRange(0, 3);
	FVector position = Enemy->GetTeleportPoint(index);

	Enemy->SetActorLocation(position);

	Enemy->PlayAnimMontage(Enemy->GetStunMontage());
	Enemy->SetStun(true);

	return EBTNodeResult::Failed;
}
