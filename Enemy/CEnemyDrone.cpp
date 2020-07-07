#include "CEnemyDrone.h"
#include "Global.h"

ACEnemyDrone::ACEnemyDrone()
{
	RowName = FName("4");

	ConstructorHelpers::FObjectFinder<UAnimMontage> attack(L"/Game/Enemy/Montages/DroneAttack");
	if (attack.Succeeded()) AttackMontage = attack.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> death(L"/Game/Enemy/Montages/DroneDeath");
	if (death.Succeeded()) DeathMontage = death.Object;

	ConstructorHelpers::FObjectFinder<UParticleSystem> explosion(TEXT("ParticleSystem'/Game/SciFiWeapDark/FX/Particles/P_Grenade_Explosion_Dark.P_Grenade_Explosion_Dark'"));
	if (explosion.Succeeded()) Explosion = explosion.Object;
}