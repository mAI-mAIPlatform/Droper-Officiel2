// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "LeanComponent.h"
ULeanComponent::ULeanComponent() { PrimaryComponentTick.bCanEverTick = true; }
void ULeanComponent::TickComponent(float DT, ELevelTick T, FActorComponentTickFunction* F) { Super::TickComponent(DT, T, F); CurrentLeanAlpha = FMath::FInterpTo(CurrentLeanAlpha, TargetLean, DT, LeanSpeed); }
void ULeanComponent::SetLeanDirection(float Dir) { TargetLean = FMath::Clamp(Dir, -1.0f, 1.0f); }
FVector ULeanComponent::GetLeanOffset() const { return FVector(0, CurrentLeanAlpha * LeanOffset, 0); }
float ULeanComponent::GetLeanRoll() const { return CurrentLeanAlpha * LeanRollAngle; }
