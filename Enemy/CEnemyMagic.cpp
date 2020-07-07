#include "CEnemyMagic.h"
#include "Global.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"

ACEnemyMagic::ACEnemyMagic()
{
	RowName = FName("3");

	ConstructorHelpers::FObjectFinder<UAnimMontage> attack(L"/Game/Enemy/Montages/MagicAttack");
	if (attack.Succeeded()) AttackMontage = attack.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> backStep(L"/Game/Enemy/Montages/BackStep");
	if (backStep.Succeeded()) BackStepMontage = backStep.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> damage(L"/Game/Enemy/Montages/RangeDamage");
	if (damage.Succeeded()) DamageMontage = damage.Object;

	ConstructorHelpers::FObjectFinder<UParticleSystem> explosion(TEXT("ParticleSystem'/Game/SciFiWeapDark/FX/Particles/P_Grenade_Explosion_Light.P_Grenade_Explosion_Light'"));
	if (explosion.Succeeded()) Explosion = explosion.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> death(L"/Game/Enemy/Montages/MeleeDeath");
	if (death.Succeeded()) DeathMontage = death.Object;
}

void ACEnemyMagic::Tick(float DeltaTime)
{
	if (GetDead())
	{
		if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(AttackMontage))
			GetMesh()->GetAnimInstance()->Montage_Pause(AttackMontage);
	}

	Super::Tick(DeltaTime);
}