#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMedKit.generated.h"

UCLASS()
class CHARACTERCPP_API ACMedKit : public AActor
{
	GENERATED_BODY()
	
public:	
	ACMedKit();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
		void OnBeginOverlap
		(
			class UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromeSweep,
			const FHitResult& SweepResult
		);

public:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* Glare;

	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* Sphere;

protected:
	float HealRatio;
};
