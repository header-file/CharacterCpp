#include "COnCameraShake.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Player/CPlayerController.h"
#include "Camera/CameraComponent.h"
#include "CCameraShake.h"
#include "Camera/CameraShake.h"

UCOnCameraShake::UCOnCameraShake()
{
	ConstructorHelpers::FClassFinder<UCameraShake> shake
	(
		L"/Game/Effects/BpCCameraShake.BpCCameraShake_C"
	);

	if (shake.Succeeded())
		CameraShakeClass = shake.Class;
}

void UCOnCameraShake::OnFire(ACPlayer * Player)
{
	APlayerController* controller = Player->GetWorld()->GetFirstPlayerController();
	controller->PlayerCameraManager->StopAllCameraShakes(true);
	controller->PlayerCameraManager->PlayCameraShake(CameraShakeClass);
}
