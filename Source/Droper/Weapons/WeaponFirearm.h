// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Weapons/WeaponBase.h"
#include "WeaponFirearm.generated.h"

UCLASS(Abstract, Blueprintable)
class DROPER_API AWeaponFirearm : public AWeaponBase
{
	GENERATED_BODY()
public:
	AWeaponFirearm();
	virtual void FireShot() override;
	UFUNCTION(BlueprintPure) float GetCurrentSpread() const;
protected:
	UPROPERTY(EditAnywhere, Category="Firearm") float BaseSpread = 1.0f;
	UPROPERTY(EditAnywhere, Category="Firearm") float ADSSpreadMultiplier = 0.3f;
	UPROPERTY(EditAnywhere, Category="Firearm") float SpreadIncreasePerShot = 0.15f;
	UPROPERTY(EditAnywhere, Category="Firearm") float SpreadRecoveryRate = 3.0f;
	UPROPERTY(EditAnywhere, Category="Firearm") float MaxSpread = 5.0f;
	float CurrentSpreadAccum = 0.0f;
};
