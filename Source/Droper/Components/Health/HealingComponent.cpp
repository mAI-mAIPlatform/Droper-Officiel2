// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "HealingComponent.h"
UHealingComponent::UHealingComponent() { PrimaryComponentTick.bCanEverTick = true; }
void UHealingComponent::TickComponent(float DT, ELevelTick T, FActorComponentTickFunction* F)
{
	Super::TickComponent(DT, T, F);
	if (!bIsHealing) return;
	HealTimer += DT;
	if (HealTimer >= HealDuration) { bIsHealing = false; OnHealComplete.Broadcast(TargetPart, HealAmount); }
}
void UHealingComponent::StartHealing(float Amount, float Duration, int32 Part) { bIsHealing = true; HealAmount = Amount; HealDuration = Duration; TargetPart = Part; HealTimer = 0.0f; }
void UHealingComponent::CancelHealing() { bIsHealing = false; HealTimer = 0.0f; }
float UHealingComponent::GetHealProgress() const { return HealDuration > 0 ? HealTimer / HealDuration : 0.0f; }
