// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "WeaponSniper.h"
AWeaponSniper::AWeaponSniper()
{
	WeaponStats.Category = EWeaponCategory::SniperRifle;
	WeaponStats.FireRate = 40.0f; WeaponStats.BaseDamage = 85.0f; WeaponStats.MagazineSize = 5;
	WeaponStats.ReloadTime = 3.5f; WeaponStats.EffectiveRange = 15000.0f; WeaponStats.MaxRange = 30000.0f;
	WeaponStats.AvailableFireModes = { EFireMode::Semi };
	BaseSpread = 0.1f; ADSSpreadMultiplier = 0.05f;
}
