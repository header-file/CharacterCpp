#pragma once

#include "CoreMinimal.h"
#include "Enemy/CEnemy.h"
#include "CEnemyRange.generated.h"

UCLASS()
class CHARACTERCPP_API ACEnemyRange : public ACEnemy
{
	GENERATED_BODY()
	
public:
	ACEnemyRange();
	void Tick(float DeltaTime) override;

	class UAnimMontage* GetReloadMontage() { return ReloadMontage; }

	void FinishReload();

protected:
	class UAnimMontage* ReloadMontage;
};
