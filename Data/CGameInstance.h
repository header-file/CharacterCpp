#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CGameInstance.generated.h"

UCLASS()
class CHARACTERCPP_API UCGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void SetData(float HP, float MP, int CurBullet, int StoreBullet);

	UFUNCTION(BlueprintPure)
		float GetCurHP() { return CurrentHP; }

	UFUNCTION(BlueprintPure)
		float GetCurMP() { return CurrentMP; }

	UFUNCTION(BlueprintPure)
		int GetCurBullets() { return CurrentBullets; }

	UFUNCTION(BlueprintPure)
		int GetStoredBullets() { return StoredBullets; }

private:
	UPROPERTY(EditAnywhere, Category = "Data")
		float CurrentHP;

	UPROPERTY(EditAnywhere, Category = "Data")
		float CurrentMP;

	UPROPERTY(EditAnywhere, Category = "Data")
		int CurrentBullets;

	UPROPERTY(EditAnywhere, Category = "Data")
		int StoredBullets;

};
