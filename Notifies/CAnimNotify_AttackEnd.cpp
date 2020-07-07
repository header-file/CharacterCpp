#include "CAnimNotify_AttackEnd.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Enemy/CEnemy.h"
#include "Components/SkeletalMeshComponent.h"

void UCAnimNotify_AttackEnd::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::Notify(MeshComp, Animation);

	ACPlayer* Player = Cast<ACPlayer>(MeshComp->GetOwner());
	if (Player != NULL)
		Player->AttackEnd();
	else
	{
		ACEnemy* Enemy = Cast<ACEnemy>(MeshComp->GetOwner());
		if (Enemy != NULL)
			Enemy->AttackEnd();
	}

}
