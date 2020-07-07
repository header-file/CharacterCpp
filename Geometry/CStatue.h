#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CStatue.generated.h"

UCLASS()
class CHARACTERCPP_API ACStatue : public AActor
{
	GENERATED_BODY()

public:
	ACStatue();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadWrite)
		bool bStart;

	UPROPERTY(BlueprintReadWrite)
		bool bCharacterOn;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;
};
