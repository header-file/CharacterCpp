#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CArrow.generated.h"

UCLASS()
class CHARACTERCPP_API ACArrow : public AActor
{
	GENERATED_BODY()
	
public:	
	ACArrow();

protected:
	virtual void BeginPlay() override;

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
	virtual void Tick(float DeltaTime) override;

	void FireInDirection(const FVector& ShootDir);

public:
	class UCapsuleComponent* GetCapsuleComponent() { return Capsule; }
	class UProjectileMovementComponent* GetProjectileComponent() { return Projectile; }

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Movement")
		class UProjectileMovementComponent* Projectile;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UCapsuleComponent* Capsule;

private:
	float Damage;

};
