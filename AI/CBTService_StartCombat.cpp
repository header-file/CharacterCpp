#include "CBTService_StartCombat.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "Enemy/CAIController.h"

void UCBTService_StartCombat::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	Controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	BB = Controller->GetBB();

	BB->SetValueAsBool("IsBattleStart", true);
}
