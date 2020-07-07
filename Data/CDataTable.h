#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "CDataTable.generated.h"

USTRUCT(BlueprintType)
struct FEnemyData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		FString Blueprint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		FString BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		FString Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		FName WeaponSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		float Mana;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		float MaxWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		float SightRadius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		float StartChaseRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		float EndChaseRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		float AlarmRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		float RestartRange;
};

UCLASS()
class CHARACTERCPP_API UCDataTable : public UObject
{
	GENERATED_BODY()
	
public:
	UCDataTable();

	const FEnemyData* GetEnemyRow(FName RowName);

private:
	const FString EnemyPath = "/Game/Enemy/EnemySheet";

	UDataTable* EnemyDataTable;
};
