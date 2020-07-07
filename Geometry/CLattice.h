#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CLattice.generated.h"

UCLASS()
class CHARACTERCPP_API ACLattice : public AActor
{
	GENERATED_BODY()
	
public:	
	ACLattice();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadWrite)
		bool bStart;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* StaticMesh;

private:
	float UpperHeight;
	float StartHeight;
};
