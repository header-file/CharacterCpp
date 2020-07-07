#include "CRunWall.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

ACRunWall::ACRunWall()
{
 	PrimaryActorTick.bCanEverTick = true;

	Wall = CreateDefaultSubobject<UStaticMeshComponent>("Wall");
	RootComponent = Wall;

	ForwardBox = CreateDefaultSubobject<UBoxComponent>("ForwardBox");
	ForwardBox->SetupAttachment(Wall);

	BackBox = CreateDefaultSubobject<UBoxComponent>("BackBox");
	BackBox->SetupAttachment(Wall);
}

void ACRunWall::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACRunWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACRunWall::CalculateDirection(ACPlayer * Player)
{
	if (Player->GetDrawn()) return;

	if (bStart)
	{
		bStart = false;

		Player->SetCanMove(true);
		Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}
	else
	{
		bStart = true;

		FVector actorForward = Player->GetActorForwardVector();
		FVector wallForward = GetActorForwardVector();

		float z = UKismetMathLibrary::Cross_VectorVector(actorForward, wallForward).Z;

		if (z > 0.0f)	//Left
		{
			FVector boxLoc = ForwardBox->GetComponentLocation();
			if (boxLoc.Y > Wall->GetComponentLocation().Y)
				boxLoc.Y += 30.0f;
			else
				boxLoc.Y -= 30.0f;

			Player->SetCanMove(false);
			Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
			Player->SetActorLocation(FVector(boxLoc.X, boxLoc.Y, Player->GetActorLocation().Z));
			Player->SetActorRotation(ForwardBox->GetComponentRotation());

			Player->PlayAnimMontage(Player->GetWallRunLeftMontage());
		}
		else if (z < 0.0f)	//Right
		{
			FVector boxLoc = BackBox->GetComponentLocation();
			if (boxLoc.Y > Wall->GetComponentLocation().Y)
				boxLoc.Y += 30.0f;
			else
				boxLoc.Y -= 30.0f;

			Player->SetCanMove(false);
			Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
			Player->SetActorLocation(FVector(boxLoc.X, boxLoc.Y, Player->GetActorLocation().Z));
			Player->SetActorRotation(BackBox->GetComponentRotation());

			Player->PlayAnimMontage(Player->GetWallRunRightMontage());
		}
	}
}

