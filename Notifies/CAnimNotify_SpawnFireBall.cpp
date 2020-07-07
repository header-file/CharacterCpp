#include "CAnimNotify_SpawnFireBall.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Player/CFireBall.h"
#include "Components/SkeletalMeshComponent.h"

void UCAnimNotify_SpawnFireBall::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::Notify(MeshComp, Animation);

	ACPlayer* Player = Cast<ACPlayer>(MeshComp->GetOwner());
	if (Player == NULL) return;

	/*FActorSpawnParameters params;
	params.Owner = Player;
	FTransform transform = FTransform::Identity;
	transform.SetRotation(Player->GetMesh()->GetSocketRotation(FName("HandR_Magic")).Quaternion());
	transform.SetTranslation(Player->GetMesh()->GetSocketLocation(FName("HandR_Magic")));

	UClass* className = Player->GetFireBallClass();
	ACFireBall* fireBall = GetWorld()->SpawnActor<ACFireBall>(className, transform, params);
	if (fireBall != NULL)
	{
		FVector direction = transform.GetRotation().Euler();
		fireBall->FireInDirection(direction);
	}*/

	//Player->SpawnFireBall();
}
