#pragma once

#include "CoreMinimal.h"
#include "Engine/DecalActor.h"
#include "CDecalActor_Warning.generated.h"

UCLASS()
class CHARACTERCPP_API ACDecalActor_Warning : public ADecalActor
{
	GENERATED_BODY()
	
public:
	ACDecalActor_Warning();

	void OnActorDestroyed();

protected:
	void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
		class UParticleSystem* Explosion;

private:
	class USoundBase* ExplosionSoundBase;
};
