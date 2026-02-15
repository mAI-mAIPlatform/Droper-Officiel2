// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "HemorrhageEffect.h"
UHemorrhageEffect::UHemorrhageEffect() { PrimaryComponentTick.bCanEverTick = true; }
void UHemorrhageEffect::TickComponent(float DT, ELevelTick T, FActorComponentTickFunction* F)
{
	Super::TickComponent(DT, T, F);
	if (bBleeding) { float Dmg = BleedRate * DT; OnBleedTick.Broadcast(Dmg); }
}
void UHemorrhageEffect::StartBleeding(float Rate) { bBleeding = true; BleedRate = Rate; BandageProgress = 0.0f; }
void UHemorrhageEffect::ApplyBandage() { bBleeding = false; BleedRate = 0.0f; }
