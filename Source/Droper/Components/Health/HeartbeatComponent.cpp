// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "HeartbeatComponent.h"
UHeartbeatComponent::UHeartbeatComponent() { PrimaryComponentTick.bCanEverTick = true; }
void UHeartbeatComponent::TickComponent(float DT, ELevelTick T, FActorComponentTickFunction* F)
{
	Super::TickComponent(DT, T, F);
	float TargetBPM = RestingBPM + (MaxBPM - RestingBPM) * FMath::Max3(StaminaFactor, DamageFactor, AdrenalineFactor);
	CurrentBPM = FMath::FInterpTo(CurrentBPM, TargetBPM, DT, CurrentBPM > TargetBPM ? RecoveryRate : 15.0f);
	CurrentBPM = FMath::Clamp(CurrentBPM, RestingBPM, MaxBPM);
}
void UHeartbeatComponent::SetStaminaFactor(float F) { StaminaFactor = FMath::Clamp(F, 0.0f, 1.0f); }
void UHeartbeatComponent::SetDamageFactor(float F) { DamageFactor = FMath::Clamp(F, 0.0f, 1.0f); }
void UHeartbeatComponent::SetAdrenalineFactor(float F) { AdrenalineFactor = FMath::Clamp(F, 0.0f, 1.0f); }
