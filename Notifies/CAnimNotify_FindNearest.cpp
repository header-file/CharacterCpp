#include "CAnimNotify_FindNearest.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Enemy/CEnemyMelee.h"
#include "Enemy/CAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SkeletalMeshComponent.h"

void UCAnimNotify_FindNearest::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACEnemyMelee* enemy = Cast<ACEnemyMelee>(MeshComp->GetOwner());
	if (enemy == NULL) return;

	ACAIController* controller = Cast<ACAIController>(enemy->GetController());
	UBlackboardComponent* BB = controller->GetBB();

	ACPlayer * player = Cast<ACPlayer>(BB->GetValueAsObject("Player"));
	if (player == NULL) return;


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