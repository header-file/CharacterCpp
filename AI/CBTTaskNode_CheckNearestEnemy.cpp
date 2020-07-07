#include "CBTTaskNode_CheckNearestEnemy.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "Enemy/CEnemyMelee.h"
#include "Enemy/CAIController.h"
#include "Player/CPlayer.h"

UCBTTaskNode_CheckNearestEnemy::UCBTTaskNode_CheckNearestEnemy()
{
	ConstructorHelpers::FClassFinder<ACEnemyMelee> enemyMelee(L"/Game/Enemy/BpCEnemyMelee");
	if (enemyMelee.Succeeded()) EnemyClass = enemyMelee.Class;

}

EBTNodeResult::Type UCBTTaskNode_CheckNearestEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	BB = Controller->GetBB();

	Enemy = Cast<ACEnemy>(Controller->GetPawn());

	ACPlayer * player = Cast<ACPlayer>(BB->GetValueAsObject("Player"));
	CheckNullResult(player, EBTNodeResult::Failed);

	TArray<AActor*> enemies;
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), EnemyClass, enemies);

	float selfDistance = Enemy->GetDistanceTo(player);

	for (AActor* enemy : enemies)
	{
		float dist = enemy->GetActorLocation().Dist(enemy->GetActorLocation(), player->GetActorLocation());
		
		if (selfDistance <= dist)
			Controller->GetBB()->SetValueAsObject("NearestEnemy", Enemy);
		else
			Controller->GetBB()->SetValueAsObject("NearestEnemy", enemy);
	}

	return EBTNodeResult::Succeeded;
}