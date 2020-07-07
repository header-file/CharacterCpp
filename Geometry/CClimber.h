#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CClimber.generated.h"

UCLASS()
class CHARACTERCPP_API ACClimber : public AActor
{
	GENERATED_BODY()
	
public:	
	ACClimber();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadWrite)
		bool bStart;
};
