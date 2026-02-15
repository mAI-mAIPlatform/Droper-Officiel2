// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "WeaponFirearm.h"
AWeaponFirearm::AWeaponFirearm() {}
void AWeaponFirearm::FireShot()
{
	CurrentSpreadAccum = FMath::Min(CurrentSpreadAccum + SpreadIncreasePerShot, MaxSpread);
	Super::FireShot();
}
float AWeaponFirearm::GetCurrentSpread() const
{
	float Spread = BaseSpread + CurrentSpreadAccum;
	return IsADS() ? Spread * ADSSpreadMultiplier : Spread;
}
