#include "CAnimNotifyState_Equipped.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Player/CSword.h"
#include "Player/CRifle.h"
#include "Components/SkeletalMeshComponent.h"

void UCAnimNotifyState_Equipped::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	ACPlayer* Player = Cast<ACPlayer>(MeshComp->GetOwner());
	if (Player == NULL) return;

	Player->SetCanMove(false);

	if (Player->GetMelee() == true)
	{
		Player->GetRifle()->AttachToComponent
		(
			MeshComp,
			FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
			FName("RifleHolster")
		);

		Player->GetSword()->AttachToComponent
		(
			MeshComp,
			FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
			FName("Knife")
		);
	}
	else if (Player->GetRange() == true)
	{
		Player->GetSword()->AttachToComponent
		(
			MeshComp,
			FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
			FName("KnifeHolster")
		);

		Player->GetRifle()->AttachToComponent
		(
			MeshComp,
			FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
			FName("Rifle")
		);
	}
	else if (Player->GetMagic() == true)
	{
		Player->GetSword()->AttachToComponent
		(
			MeshComp,
			FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
			FName("KnifeHolster")
		);

		Player->GetRifle()->AttachToComponent
		(
			MeshComp,
			FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
			FName("RifleHolster")
		);
	}
}

void UCAnimNotifyState_Equipped::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UCAnimNotifyState_Equipped::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	ACPlayer* Player = Cast<ACPlayer>(MeshComp->GetOwner());
	if (Player == NULL) return;

	Player->Equipped();
}
