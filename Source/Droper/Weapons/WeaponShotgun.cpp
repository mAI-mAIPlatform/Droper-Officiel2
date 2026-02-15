// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "WeaponShotgun.h"
AWeaponShotgun::AWeaponShotgun()
{
	WeaponStats.Category = EWeaponCategory::Shotgun;
	WeaponStats.FireRate = 80.0f; WeaponStats.BaseDamage = 12.0f; WeaponStats.MagazineSize = 8;
	WeaponStats.ReloadTime = 0.5f; WeaponStats.EffectiveRange = 1500.0f; WeaponStats.MaxRange = 3000.0f;
	WeaponStats.AvailableFireModes = { EFireMode::Semi };
	BaseSpread = 3.0f;
}
void AWeaponShotgun::FireShot()
{
	// Fires multiple pellets per shot
	for (int32 i = 0; i < PelletCount; i++) { Super::FireShot(); }
	// Only consume 1 ammo for all pellets — already consumed in base
}
