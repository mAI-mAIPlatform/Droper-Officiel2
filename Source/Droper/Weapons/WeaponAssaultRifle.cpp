// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "WeaponAssaultRifle.h"
AWeaponAssaultRifle::AWeaponAssaultRifle()
{
	WeaponStats.Category = EWeaponCategory::AssaultRifle;
	WeaponStats.FireRate = 700.0f; WeaponStats.BaseDamage = 32.0f; WeaponStats.MagazineSize = 30;
	WeaponStats.ReloadTime = 2.2f; WeaponStats.EffectiveRange = 4000.0f; WeaponStats.MaxRange = 8000.0f;
	WeaponStats.AvailableFireModes = { EFireMode::Auto, EFireMode::Semi };
	BaseSpread = 1.2f; ADSSpreadMultiplier = 0.25f;
}
