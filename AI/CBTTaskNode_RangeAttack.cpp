#include "CBTTaskNode_RangeAttack.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "Enemy/CAIController.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Player/CPlayer.h"

EBTNodeResult::Type UCBTTaskNode_RangeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	BB = Controller->GetBB();

	Enemy = Cast<ACEnemy>(Controller->GetPawn());
	if (Enemy->GetAttacking()) return EBTNodeResult::Succeeded;
	if (Enemy->GetBackStepping()) return EBTNodeResult::Succeeded;

	ACPlayer * player = Cast<ACPlayer>(BB->GetValueAsObject("Player"));
	CheckNullResult(player, EBTNodeResult::Failed);

	Enemy->PlayAnimMontage(Enemy->GetAttackMontage());

	Enemy->SetAttacking(true);

	FVector start = Enemy->GetMesh()->GetSocketLocation("Muzzle");
	FVector end = start + Enemy->GetActorForwardVector() * 1000.0f;

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

	return EBTNodeResult::Succeeded;
}