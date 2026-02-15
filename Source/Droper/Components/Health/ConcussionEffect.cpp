// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "ConcussionEffect.h"
UConcussionEffect::UConcussionEffect() { PrimaryComponentTick.bCanEverTick = true; }
void UConcussionEffect::TickComponent(float DT, ELevelTick T, FActorComponentTickFunction* F) { Super::TickComponent(DT, T, F); if (ConcussionTimer > 0) ConcussionTimer -= DT; }
void UConcussionEffect::ApplyConcussion(float Severity) { ConcussionSeverity = FMath::Clamp(Severity, 0.0f, 1.0f); ConcussionTimer = MaxConcussionDuration * Severity; }
float UConcussionEffect::GetBlurIntensity() const { return IsConcussed() ? MaxBlur * (ConcussionTimer / (MaxConcussionDuration * ConcussionSeverity)) : 0.0f; }
float UConcussionEffect::GetInputDelay() const { return IsConcussed() ? MaxInputDelay * ConcussionSeverity : 0.0f; }
float UConcussionEffect::GetTinnitusVolume() const { return IsConcussed() ? ConcussionSeverity : 0.0f; }
