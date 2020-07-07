#include "CGameInstance.h"

void UCGameInstance::SetData(float HP, float MP, int CurBullet, int StoreBullet)
{
	CurrentHP = HP;
	CurrentMP = MP;
	CurrentBullets = CurBullet;
	StoredBullets = StoreBullet;
}