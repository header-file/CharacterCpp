#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDestructibleBarrel.generated.h"

UCLASS()
class CHARACTERCPP_API ACDestructibleBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDestructibleBarrel();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
		void OnBeginOverlap
		(
			class UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult & SweepResult
		);

protected:
	UPROPERTY(BlueprintReadOnly)
		bool bDamaged;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UDestructibleComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

};