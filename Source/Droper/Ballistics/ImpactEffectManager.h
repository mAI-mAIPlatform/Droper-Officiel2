// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "ImpactEffectManager.generated.h"
UENUM(BlueprintType) enum class ESurfaceResponse : uint8 { Default, Metal, Wood, Concrete, Glass, Flesh, Dirt, Water };
UCLASS(Blueprintable) class DROPER_API UImpactEffectManager : public UObject { GENERATED_BODY() public:
	UFUNCTION(BlueprintCallable) static void SpawnImpactEffect(UWorld* World, const FHitResult& Hit, ESurfaceResponse Surface);
};
