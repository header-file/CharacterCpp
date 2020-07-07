#include "CAnimNotify_GetUp.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Components/SkeletalMeshComponent.h"

void UCAnimNotify_GetUp::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::Notify(MeshComp, Animation);

	ACPlayer* Player = Cast<ACPlayer>(MeshComp->GetOwner());
	if (Player == NULL) return;

	Player->LaunchCharacter(-Player->GetActorForwardVector() * 100.0f, false, false);

	Player->PlayAnimMontage(Player->GetGetUpMontage());
}