#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSliceableWall.generated.h"

UCLASS()
class CHARACTERCPP_API ACSliceableWall : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSliceableWall();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UProceduralMeshComponent* ProceduralMesh;

};
