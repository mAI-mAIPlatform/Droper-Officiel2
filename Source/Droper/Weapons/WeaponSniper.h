// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Weapons/WeaponFirearm.h"
#include "WeaponSniper.generated.h"
UCLASS(Blueprintable) class DROPER_API AWeaponSniper : public AWeaponFirearm { GENERATED_BODY() public: AWeaponSniper();
UFUNCTION(BlueprintPure) float GetScopeZoom() const { return ScopeZoom; }
protected: UPROPERTY(EditAnywhere) float ScopeZoom = 6.0f; UPROPERTY(EditAnywhere) float ScopeSwayMultiplier = 2.0f; };
