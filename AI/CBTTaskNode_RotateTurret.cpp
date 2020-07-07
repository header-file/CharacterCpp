#include "CBTTaskNode_RotateTurret.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "Enemy/CEnemyTurret.h"
#include "Enemy/CAIController.h"
#include "Player/CPlayer.h"
#include "Components/StaticMeshComponent.h"

EBTNodeResult::Type UCBTTaskNode_RotateTurret::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	BB = Controller->GetBB();

	Enemy = Cast<ACEnemyTurret>(Controller->GetPawn());
	ACPlayer* player = Cast<ACPlayer>(BB->GetValueAsObject("Player"));
	if (player == NULL) return EBTNodeResult::Failed;

	if (BB->GetValueAsBool("IsBattleStart"))
		return EBTNodeResult::Succeeded;

	UStaticMeshComponent* body = Enemy->GetBody();

	FVector rot = body->GetComponentRotation().Vector();
	FVector target = player->GetActorLocation() - Enemy->GetActorLocation();
	rot = FMath::VInterpTo(rot, target, Enemy->GetWorld()->GetDeltaSeconds(), 2.0f);
	
	body->SetRelativeRotation(rot.Rotation().Quaternion());
	Enemy->SetCount(Enemy->GetCount() + 1);

	if (Enemy->GetCount() > 60.0f)
	{
		Enemy->SetCount(0.0f);
		BB->SetValueAsBool("IsBattleStart", true);
		return EBTNodeResult::Succeeded;
	}	
	else
		return EBTNodeResult::Failed;
}