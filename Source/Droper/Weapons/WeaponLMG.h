// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Weapons/WeaponFirearm.h"
#include "WeaponLMG.generated.h"
UCLASS(Blueprintable) class DROPER_API AWeaponLMG : public AWeaponFirearm { GENERATED_BODY() public: AWeaponLMG();
protected: UPROPERTY(EditAnywhere) float OverheatRate = 0.02f; UPROPERTY(EditAnywhere) float CooldownRate = 0.05f; float HeatLevel = 0.0f; };
