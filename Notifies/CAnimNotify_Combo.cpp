#include "CAnimNotify_Combo.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Player/CSword.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCAnimNotify_Combo::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::Notify(MeshComp, Animation);

	ACPlayer* Player = Cast<ACPlayer>(MeshComp->GetOwner());
	if (Player == NULL) return;

	Player->GetSword()->SetAttacked(false);

	if (Player->GetCombo1() && Player->GetCurrentCombo() == 1)
	{
		if (Player->GetCharacterMovement()->MovementMode == EMovementMode::MOVE_None)
			Player->PlayAnimMontage(Player->GetJumpAttackMontage());
		else
			Player->PlayAnimMontage(Player->GetCombo2AttackMontage());
	}
	else if(Player->GetCombo2() && Player->GetCurrentCombo() >= 2)
		Player->PlayAnimMontage(Player->GetCombo3AttackMontage());

}
