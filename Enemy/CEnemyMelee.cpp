#include "CEnemyMelee.h"
#include "Global.h"

ACEnemyMelee::ACEnemyMelee()
{
	RowName = FName("1");

	ConstructorHelpers::FClassFinder<ACEnemyWeapon> drill(L"/Game/Enemy/Weapons/BpCWeaponDrill.BpCWeaponDrill_C");
	if (drill.Succeeded()) WeaponClass = drill.Class;

	ConstructorHelpers::FObjectFinder<UAnimMontage> attack(L"/Game/Enemy/Montages/MeleeAttack");
	if (attack.Succeeded()) AttackMontage = attack.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> death(L"/Game/Enemy/Montages/MeleeDeath");
	if (death.Succeeded()) DeathMontage = death.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> backStep(L"/Game/Enemy/Montages/MeleeTumbling");
	if (backStep.Succeeded()) BackStepMontage = backStep.Object;
}

void ACEnemyMelee::BeginPlay()
{
	Super::BeginPlay();


}

void ACEnemyMelee::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}
