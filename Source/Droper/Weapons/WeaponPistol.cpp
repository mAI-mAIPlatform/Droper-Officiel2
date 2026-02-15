// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "WeaponPistol.h"
AWeaponPistol::AWeaponPistol()
{
	WeaponStats.Category = EWeaponCategory::Pistol;
	WeaponStats.FireRate = 400.0f; WeaponStats.BaseDamage = 28.0f; WeaponStats.MagazineSize = 15;
	WeaponStats.ReloadTime = 1.5f; WeaponStats.EffectiveRange = 2500.0f; WeaponStats.MaxRange = 5000.0f;
	WeaponStats.AvailableFireModes = { EFireMode::Semi };
	BaseSpread = 1.0f; ADSSpreadMultiplier = 0.3f;
}
