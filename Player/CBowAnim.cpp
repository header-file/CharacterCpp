#include "CBowAnim.h"
#include "Global.h"
#include "CBow.h"

void UCBowAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Bow = Cast<ACBow>(TryGetPawnOwner());
}

void UCBowAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(Bow);

	Alpha = Bow->Alpha;
}
