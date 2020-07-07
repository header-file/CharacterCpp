#include "CBTTaskNode_Dash.h"
#include "Global.h"
#include "Enemy/CEnemyBoss.h"
#include "Enemy/CAIController.h"
#include "Player/CPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UCBTTaskNode_Dash::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	BB = Controller->GetBB();
	if (BB->GetValueAsFloat("HPRate") > 0.5f) return EBTNodeResult::Succeeded;

	Enemy = Cast<ACEnemyBoss>(Controller->GetPawn());
	if (Enemy->GetAttacking()) return EBTNodeResult::Failed;

	ACPlayer * player = Cast<ACPlayer>(BB->GetValueAsObject("Player"));
	CheckNullResult(player, EBTNodeResult::Failed);

	if (player->GetDead() == true) return EBTNodeResult::Failed;

	float distance = BB->GetValueAsFloat("Distance");
	if (distance <= 200.0f) return EBTNodeResult::Succeeded;

	
	if(!Enemy->GetDash())
		BB->SetValueAsVector("SelfLocation", Enemy->GetActorLocation());
	
	if (distance >= 1000.0f)
	{
		BB->SetValueAsVector("JumpTo", player->GetActorLocation());
		//Enemy->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
		Enemy->SetDash(true);
		Enemy->GetCharacterMovement()->MaxWalkSpeed = 2000.0f;
	}

	if (Enemy->GetDash())
	{
		FVector location = BB->GetValueAsVector("JumpTo");
		/*FPathFollowingResult result = */Controller->MoveToLocation(location, 50.0f);

		FVector startLocation = BB->GetValueAsVector("SelfLocation");
		FVector nowLocation = Enemy->GetActorLocation();
		float dist = FVector::Dist(startLocation, nowLocation);

		FVector playerLocation = player->GetActorLocation();
		float pDist = FVector::Dist(playerLocation, nowLocation);

		//if (result.Code == EPathFollowingResult::Success)
		if(dist >= 1000.0f || pDist <= 150.0f)
		{
			//Enemy->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
			Enemy->GetCharacterMovement()->MaxWalkSpeed = Enemy->GetWalkSpeed();
			Enemy->SetDash(false);

			FVector start = Enemy->GetActorLocation();

			TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
			ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
			ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

			TArray<AActor*> IgnoreActors;
			IgnoreActors.Add(Enemy);

			TArray<AActor*> hitActors;

			DrawDebugSphere(Enemy->GetWorld(), start, 300.0f, 20, FColor::Red);
			bool bHit = UKismetSystemLibrary::SphereOverlapActors(Enemy->GetWorld(), start, 300.0f, ObjectTypes, NULL, IgnoreActors, hitActors);

			if (bHit)
			{
				for (auto& hit : hitActors)
				{
					//CLog::Print(hit->GetName());

					UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>(hit->GetRootComponent());

					if (mesh != NULL)
						mesh->AddRadialImpulse(Enemy->GetActorLocation(), 500.0f, 2500.0f, ERadialImpulseFalloff::RIF_Linear, true);
					else
					{
						player = Cast<ACPlayer>(hit);
						if (player == NULL) continue;

						/*USkeletalMeshComponent* skeletalMesh = player->GetMesh();

						if (skeletalMesh != NULL)
						{
							skeletalMesh->SetSimulatePhysics(true);
							skeletalMesh->SetAllBodiesSimulatePhysics(true);
							skeletalMesh->WakeAllRigidBodies();
							skeletalMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
							skeletalMesh->AddRadialImpulse(Enemy->GetActorLocation(), 500.0f, 500.0f, ERadialImpulseFalloff::RIF_Linear, true);
						}*/

						player->Damage(DamageType::HEAVY, Enemy->GetDamage());
					}
				}
			}

			return EBTNodeResult::Failed;
		}
	}

	return EBTNodeResult::Failed;
}
