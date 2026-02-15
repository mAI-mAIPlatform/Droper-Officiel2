// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Weapons/WeaponFirearm.h"
#include "WeaponShotgun.generated.h"
UCLASS(Blueprintable) class DROPER_API AWeaponShotgun : public AWeaponFirearm { GENERATED_BODY() public: AWeaponShotgun(); virtual void FireShot() override;
protected: UPROPERTY(EditAnywhere) int32 PelletCount = 8; UPROPERTY(EditAnywhere) float PelletSpread = 5.0f; };
