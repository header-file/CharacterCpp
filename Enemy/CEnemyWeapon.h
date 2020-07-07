#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEnemyWeapon.generated.h"

UCLASS()
class CHARACTERCPP_API ACEnemyWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ACEnemyWeapon();

	void SetDamage(float val) { Damage = val; }
	void SetProjectileRange(float val) { ProjectileRange = val; }
	class UCapsuleComponent* GetCapsule() { return Capsule; }

	void ToggleCollision();

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

private:
	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere)
		float Damage;

	UPROPERTY(VisibleAnywhere)
		float ProjectileRange;

private:
	class ACEnemy* Owner;

	bool bCollisionOn;

};
