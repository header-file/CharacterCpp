#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CRuneStone.generated.h"

UCLASS()
class CHARACTERCPP_API ACRuneStone : public AActor
{
	GENERATED_BODY()
	
public:	
	ACRuneStone();

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
		bool bPurified;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UDestructibleComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

private:
	class UMaterial* Material;
	class UMaterialInstanceDynamic* MaterialDynamic;

	float ColorChange = 0.0f;

	class ACPlayer* Player;
};
