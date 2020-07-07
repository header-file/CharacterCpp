#include "CBTService_CheckNearest.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Enemy/CEnemyMelee.h"
#include "Enemy/CAIController.h"

void UCBTService_CheckNearest::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	Controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	BB = Controller->GetBB();

	Enemy = Cast<ACEnemyMelee>(Controller->GetPawn());
	if (Enemy == NULL) return;

	ACPlayer * player = Cast<ACPlayer>(BB->GetValueAsObject("Player"));
	if (player == NULL) return;

	//BB->SetValueAsObject("NearestEnemy", NULL);

	if (BB->GetValueAsObject("NearestEnemy") == NULL)
	{
		ACEnemyMelee* enemies[10] = { NULL, };
		int index = 0;
		ACEnemyMelee* nearest = NULL;

		for (int i = 0; i < 10; i++)
		{
			ACEnemyMelee* melee = Cast<ACEnemyMelee>(player->GetTarget(i));
			if (melee != NULL)
			{
				enemies[index] = melee;
				index++;
			}
		}
		nearest = enemies[0];
		if (nearest == NULL)
		{
			for (int i = 1; i < 10; i++)
			{
				nearest = enemies[i];

				if (nearest != NULL)
					break;
				else
					continue;
			}
		}
		if (nearest == NULL) return;

		float nearDistance = FVector::Distance(nearest->GetActorLocation(), player->GetActorLocation());

		for (int i = 1; i < index; i++)
		{
			float dist = FVector::Distance(enemies[i]->GetActorLocation(), player->GetActorLocation());

			if (nearDistance > dist)
			{
				nearest = enemies[i];
				nearDistance = dist;
			}
		}

		Cast<ACAIController>(nearest->GetController())->GetBB()->SetValueAsObject("NearestEnemy", nearest);
		//BB->SetValueAsObject("NearestEnemy", nearest);
	}
}