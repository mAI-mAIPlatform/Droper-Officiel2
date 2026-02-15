// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "WeaponSwayComponent.h"
UWeaponSwayComponent::UWeaponSwayComponent() { PrimaryComponentTick.bCanEverTick = true; }
void UWeaponSwayComponent::TickComponent(float DT, ELevelTick T, FActorComponentTickFunction* F)
{
	Super::TickComponent(DT, T, F);
	SwayTime += DT;
	float Amp = BaseSwayAmplitude * (1.0f + HeartbeatMod + StaminaMod);
	if (bHoldingBreath) Amp *= 0.1f;
	SwayOffset.X = FMath::Sin(SwayTime * BaseSwayFrequency * 2.0f) * Amp;
	SwayOffset.Y = FMath::Sin(SwayTime * BaseSwayFrequency) * Amp * 0.7f;
}
void UWeaponSwayComponent::SetHeartbeatFactor(float F) { HeartbeatMod = F; }
void UWeaponSwayComponent::SetStaminaFactor(float F) { StaminaMod = F; }
void UWeaponSwayComponent::SetBreathHold(bool bH) { bHoldingBreath = bH; }
