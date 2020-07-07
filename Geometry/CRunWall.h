#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CRunWall.generated.h"

UCLASS()
class CHARACTERCPP_API ACRunWall : public AActor
{
	GENERATED_BODY()
	
public:	
	ACRunWall();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
		void CalculateDirection(class ACPlayer * Player);

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* ForwardBox;

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* BackBox;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Wall;

private:
	bool bStart;
};
