#include "CAnimNotify_SpawnLightning.h"
#include "Global.h"
#include "Player/CPlayer.h"

void UCAnimNotify_SpawnLightning::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::Notify(MeshComp, Animation);

	ACPlayer* Player = Cast<ACPlayer>(MeshComp->GetOwner());
	if (Player == NULL) return;

	Player->SpawnLightning();
}
