// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "WeaponDMR.h"
AWeaponDMR::AWeaponDMR()
{
	WeaponStats.Category = EWeaponCategory::DMR;
	WeaponStats.FireRate = 180.0f; WeaponStats.BaseDamage = 55.0f; WeaponStats.MagazineSize = 10;
	WeaponStats.ReloadTime = 2.8f; WeaponStats.EffectiveRange = 8000.0f; WeaponStats.MaxRange = 15000.0f;
	WeaponStats.AvailableFireModes = { EFireMode::Semi };
	BaseSpread = 0.5f; ADSSpreadMultiplier = 0.15f;
}
