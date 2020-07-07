#include "CEnemyRange.h"
#include "Global.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"

ACEnemyRange::ACEnemyRange()
{
	RowName = FName("2");

	ConstructorHelpers::FClassFinder<ACEnemyWeapon> rifle(L"/Game/Enemy/Weapons/BpCWeaponRifle.BpCWeaponRifle_C");
	if (rifle.Succeeded()) WeaponClass = rifle.Class;

	ConstructorHelpers::FObjectFinder<UAnimMontage> attack(L"/Game/Enemy/Montages/RangeAttack");
	if (attack.Succeeded()) AttackMontage = attack.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> reload(L"/Game/Enemy/Montages/RangeReload");
	if (reload.Succeeded()) ReloadMontage = reload.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> backStep(L"/Game/Enemy/Montages/BackStep");
	if (backStep.Succeeded()) BackStepMontage = backStep.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> damage(L"/Game/Enemy/Montages/RangeDamage");
	if (damage.Succeeded()) DamageMontage = damage.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> death(L"/Game/Enemy/Montages/MeleeDeath");
	if (death.Succeeded()) DeathMontage = death.Object;
}

void ACEnemyRange::Tick(float DeltaTime)
{
	if (GetDead())
	{
		if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(ReloadMontage))
			GetMesh()->GetAnimInstance()->Montage_Pause(ReloadMontage);
	}

	Super::Tick(DeltaTime);
}

void ACEnemyRange::FinishReload()
{
	SetAttacking(false);
}
