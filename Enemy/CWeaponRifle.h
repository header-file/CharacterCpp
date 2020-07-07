#pragma once

#include "CoreMinimal.h"
#include "Enemy/CEnemyWeapon.h"
#include "CWeaponRifle.generated.h"

UCLASS()
class CHARACTERCPP_API ACWeaponRifle : public ACEnemyWeapon
{
	GENERATED_BODY()
	
public:
	ACWeaponRifle();

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* SkeletalMesh;
};
