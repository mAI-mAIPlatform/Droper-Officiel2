// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "WeaponLMG.h"
AWeaponLMG::AWeaponLMG()
{
	WeaponStats.Category = EWeaponCategory::LMG;
	WeaponStats.FireRate = 750.0f; WeaponStats.BaseDamage = 30.0f; WeaponStats.MagazineSize = 100;
	WeaponStats.ReloadTime = 5.5f; WeaponStats.EffectiveRange = 5000.0f; WeaponStats.MaxRange = 9000.0f;
	WeaponStats.AvailableFireModes = { EFireMode::Auto };
	BaseSpread = 2.0f; ADSSpreadMultiplier = 0.4f;
}
