#include "CAnimNotify_AfterExplode.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/CPlayer.h"

void UCAnimNotify_AfterExplode::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACEnemy* Enemy = Cast<ACEnemy>(MeshComp->GetOwner());
	if (Enemy == NULL) return;

	Enemy->GetCharacterMovement()->MaxWalkSpeed = 0.0f;

	UGameplayStatics::SpawnEmitterAtLocation(Enemy->GetWorld(), Enemy->GetExplosion(), Enemy->GetActorTransform());

	FVector start = Enemy->GetActorLocation();
	
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(Enemy);

	TArray<AActor*> hitActors;

	bool bHit = UKismetSystemLibrary::SphereOverlapActors(Enemy->GetWorld(), start, 300.0f, ObjectTypes, NULL, IgnoreActors, hitActors);
	
	if (bHit)
	{
		for (auto& hit : hitActors)
		{
			//CLog::Print(hit->GetName());

			UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>(hit->GetRootComponent());
	
			if(mesh != NULL)
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

	Enemy->Destroy();
}