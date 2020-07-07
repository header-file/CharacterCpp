#include "CWeaponRifle.h"
#include "Components/SkeletalMeshComponent.h"

ACWeaponRifle::ACWeaponRifle()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");

	RootComponent = SkeletalMesh;
}