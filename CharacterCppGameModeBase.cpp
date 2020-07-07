#include "CharacterCppGameModeBase.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"

ACharacterCppGameModeBase::ACharacterCppGameModeBase()
{
	//static ConstructorHelpers::FClassFinder<APawn> player(TEXT("/Game/CyberHunter/BpCPlayer"));

	//if (player.Class != NULL)
	//	DefaultPawnClass = player.Class;

	///*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/TopDownCPP/Blueprints/TopDownCharacter'"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}*/
	//

	//ConstructorHelpers::FClassFinder<APlayerController> controller(L"/Game/CyberHunter/BpCPlayerController");

	//if (controller.Succeeded())
	//	PlayerControllerClass = controller.Class;
}