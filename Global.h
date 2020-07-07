#pragma once

#include "CLog.h"
#include "Engine/World.h"
#include "TimerManager.h"

#include "DrawDebugHelpers.h"
#include "ConstructorHelpers.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


#define CheckNull(p){ if(p == NULL) return ; }
#define CheckNullResult(p, result){ if(p == NULL) return result; }