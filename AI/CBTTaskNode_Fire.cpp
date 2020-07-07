#include "CBTTaskNode_Fire.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "Enemy/CEnemyTurret.h"
#include "Enemy/CAIController.h"
#include "Player/CPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"

EBTNodeResult::Type UCBTTaskNode_Fire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	BB = Controller->GetBB();

	Enemy = Cast<ACEnemyTurret>(Controller->GetPawn());
	ACPlayer* player = Cast<ACPlayer>(BB->GetValueAsObject("Player"));
	if (player == NULL) return EBTNodeResult::Failed;

	float count = Enemy->GetCount();
	count++;
	Enemy->SetCount(count);

	UGameplayStatics::SpawnEmitterAttached
	(
		Enemy->GetMuzzleFlash(),
		Enemy->GetMuzzle(),
		""
	);

	//Enemy->GetFireSound()->Play();
	UGameplayStatics::PlaySoundAtLocation(Enemy, Enemy->GetSound(), Enemy->GetActorLocation());
	
	FVector start = Enemy->GetMuzzle()->GetComponentLocation();
	FVector end = start + Enemy->GetBody()->GetComponentRotation().Vector() * 1000.0f;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(Enemy);

	FHitResult hitResult;
	bool bHit = UKismetSystemLibrary::LineTraceSingleForObjects(Enemy->GetWorld(), start, end, ObjectTypes, NULL, IgnoreActors, EDrawDebugTrace::ForOneFrame, hitResult, true);

	if (bHit)
	{
		player = Cast<ACPlayer>(hitResult.Actor);
		if (player != NULL)
			player->Damage(DamageType::LIGHT, Enemy->GetDamage());
		
	}
	
	
	if (Enemy->GetCount() >= 5.0f)
	{
		Enemy->SetCount(0.0f);
		BB->SetValueAsBool("IsBattleStart", false);
		return EBTNodeResult::Succeeded;
	}
	else
		return EBTNodeResult::Failed;
}