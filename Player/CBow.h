#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBow.generated.h"

UCLASS()
class CHARACTERCPP_API ACBow : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBow();

public:
	friend class UCBowAnim;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* SkeletalMesh;

private:
	float Alpha;
};
