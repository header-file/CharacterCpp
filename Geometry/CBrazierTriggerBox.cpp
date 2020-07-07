#include "CBrazierTriggerBox.h"
#include "CBrazier.h"

ACBrazierTriggerBox::ACBrazierTriggerBox()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACBrazierTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	bComplete = false;
}

void ACBrazierTriggerBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bComplete) return;

	for (int i = 0; i < 4; i++)
	{
		if (Braziers[i] == NULL) return;

		if (Braziers[i]->GetOverlapped() && Braziers[i]->GetLightOn())
		{
			switch (i)
			{
			case 0:
				break;
			case 1:
				Braziers[0]->SetLightOn(false);
				break;
			case 2:
				Braziers[0]->SetLightOn(true);
				Braziers[1]->SetLightOn(false);
				break;
			case 3:
				Braziers[0]->SetLightOn(true);
				Braziers[1]->SetLightOn(false);
				Braziers[2]->SetLightOn(false);
				break;
			default:
				break;
			}
		}
	}
}
