#include "CAnimNotify_CheckRoll.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Player/CPlayerController.h"
#include "Components/SkeletalMeshComponent.h"

void UCAnimNotify_CheckRoll::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::Notify(MeshComp, Animation);

	ACPlayer* Player = Cast<ACPlayer>(MeshComp->GetOwner());
	if (Player == NULL) return;

	if (Player->GetJumpTooHigh() == true)
	{
		Player->SetJumpTooHigh(false);
		Player->PlayAnimMontage(Player->GetRollMontage(), 1.5f);
	}
}
