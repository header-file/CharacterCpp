#pragma once

#include "CoreMinimal.h"
#include "Enemy/CEnemy.h"
#include "CEnemyMelee.generated.h"

UCLASS()
class CHARACTERCPP_API ACEnemyMelee : public ACEnemy
{
	GENERATED_BODY()
	
public:
	ACEnemyMelee();

protected:
	void BeginPlay() override;

public:
	void Tick(float DeltaTime) override;
};
