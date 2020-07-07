#include "CDataTable.h"
#include "Global.h"

UCDataTable::UCDataTable()
{
	EnemyDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, *EnemyPath));
}

const FEnemyData* UCDataTable::GetEnemyRow(FName RowName)
{
	if (EnemyDataTable == NULL) return NULL;

	return EnemyDataTable->FindRow<FEnemyData>(RowName, L"");
}