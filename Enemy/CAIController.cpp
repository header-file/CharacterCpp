#include "CAIController.h"
#include "Global.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

ACAIController::ACAIController()
{
	BT = CreateDefaultSubobject<UBehaviorTreeComponent>("BT");
	BB = CreateDefaultSubobject<UBlackboardComponent>("BB");

	angleX = UKismetMathLibrary::RandomFloatInRange(0.0f, UKismetMathLibrary::GetPI());
	angleY = UKismetMathLibrary::RandomFloatInRange(0.0f, UKismetMathLibrary::GetPI());
}

void ACAIController::StartTree(FString Path)
{
	Path = "/Game/Enemy/AI/" + Path;
	UBehaviorTree* tree = Cast<UBehaviorTree>(StaticLoadObject(UBehaviorTree::StaticClass(), NULL, *Path));

	if (tree != NULL)
	{
		BB->InitializeBlackboard(*tree->BlackboardAsset);
		BT->StartTree(*tree);
	}
}
