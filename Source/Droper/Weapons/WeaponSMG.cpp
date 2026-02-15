// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "WeaponSMG.h"
AWeaponSMG::AWeaponSMG()
{
	WeaponStats.Category = EWeaponCategory::SMG;
	WeaponStats.FireRate = 900.0f; WeaponStats.BaseDamage = 24.0f; WeaponStats.MagazineSize = 35;
	WeaponStats.ReloadTime = 1.8f; WeaponStats.EffectiveRange = 2000.0f; WeaponStats.MaxRange = 5000.0f;
	WeaponStats.AvailableFireModes = { EFireMode::Auto };
	BaseSpread = 1.5f; ADSSpreadMultiplier = 0.35f;
}
