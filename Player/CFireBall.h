#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CFireBall.generated.h"

UCLASS()
class CHARACTERCPP_API ACFireBall : public AActor
{
	GENERATED_BODY()
	
public:	
	ACFireBall();

protected:
	virtual void BeginPlay() override;

public:	
	/*UFUNCTION()
		void OnBeginHit
		(
			UPrimitiveComponent* HitComponent, 
			AActor* OtherActor, 
			UPrimitiveComponent* OtherComp, 
			FVector NormalImpulse, const FHitResult& Hit
		);*/

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
	class USphereComponent* GetSphereComponent() { return Sphere; }

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Movement")
		class UProjectileMovementComponent* Projectile;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* Sphere;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* FireBall;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystem* FireHit;

private:
	float Damage;
};
