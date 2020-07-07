#pragma once

#include "CoreMinimal.h"
#include "Enemy/CEnemy.h"
#include "CEnemyMagic.generated.h"

UCLASS()
class CHARACTERCPP_API ACEnemyMagic : public ACEnemy
{
	GENERATED_BODY()
	
public:
	ACEnemyMagic();

	void Tick(float DeltaTime) override;
};
