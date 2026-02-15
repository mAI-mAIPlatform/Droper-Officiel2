// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Weapons/WeaponBase.h"
#include "WeaponMelee.generated.h"
UCLASS(Blueprintable) class DROPER_API AWeaponMelee : public AWeaponBase { GENERATED_BODY() public: AWeaponMelee();
	virtual void StartFire() override;
protected: UPROPERTY(EditAnywhere) float MeleeRange = 200.0f; UPROPERTY(EditAnywhere) float MeleeAngle = 60.0f; };
