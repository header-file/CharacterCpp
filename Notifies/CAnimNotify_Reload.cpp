#include "CAnimNotify_Reload.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Player/CArrow.h"
#include "Components/SkeletalMeshComponent.h"

void UCAnimNotify_Reload::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::Notify(MeshComp, Animation);

	ACPlayer* Player = Cast<ACPlayer>(MeshComp->GetOwner());
	if (Player == NULL) return;

	//Player->SpawnBullet();

	//if (Player->GetBullet() == NULL) return;
}
