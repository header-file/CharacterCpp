#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEnergyCore.generated.h"

UCLASS()
class CHARACTERCPP_API ACEnergyCore : public AActor
{
	GENERATED_BODY()
	
public:	
	ACEnergyCore();

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
		void OnBeginOverlap
		(
			class UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult & SweepResult
		);

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere)
		class UParticleSystem* Explosion;
};
