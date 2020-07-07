#include "CAnimNotify_Spell.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "Enemy/CAIController.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/CPlayer.h"

void UCAnimNotify_Spell::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACEnemy* Enemy = Cast<ACEnemy>(MeshComp->GetOwner());
	if (Enemy == NULL) return;

	FVector location = Enemy->GetAIController()->GetBB()->GetValueAsVector("AttackLocation");
	FTransform transform = FTransform::Identity;
	transform.SetLocation(location);
	transform.SetScale3D(FVector(2.0f, 2.0f, 2.0f));

	UGameplayStatics::SpawnEmitterAtLocation
	(
		Enemy->GetWorld(),
		Enemy->GetExplosion(),
		transform
	);

	//Sphere Ãæµ¹
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(Enemy);

	TArray<AActor*> hitActors;

	bool bHit = UKismetSystemLibrary::SphereOverlapActors(Enemy->GetWorld(), location, 300.0f, ObjectTypes, NULL, IgnoreActors, hitActors);
	//DrawDebugSphere(Enemy->GetWorld(), location, 300.0f, 20, FColor::Blue);

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
				ACPlayer* player = Cast<ACPlayer>(hit);
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
}
