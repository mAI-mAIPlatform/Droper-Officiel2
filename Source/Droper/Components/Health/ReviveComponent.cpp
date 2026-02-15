// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "ReviveComponent.h"
UReviveComponent::UReviveComponent() { PrimaryComponentTick.bCanEverTick = true; }
void UReviveComponent::TickComponent(float DT, ELevelTick T, FActorComponentTickFunction* F)
{
	Super::TickComponent(DT, T, F);
	if (!bIsDowned) return;
	DownedTimer += DT;
	if (DownedTimer >= MaxDownedTime) { bIsDowned = false; OnBledOut.Broadcast(); return; }
	if (bIsBeingRevived) { ReviveProgress += DT; if (ReviveProgress >= ReviveDuration) { bIsDowned = false; bIsBeingRevived = false; OnRevived.Broadcast(); } }
}
void UReviveComponent::EnterDownedState() { bIsDowned = true; DownedTimer = 0.0f; ReviveProgress = 0.0f; }
void UReviveComponent::StartRevive(AActor* Reviver) { bIsBeingRevived = true; CurrentReviver = Reviver; ReviveProgress = 0.0f; }
void UReviveComponent::CancelRevive() { bIsBeingRevived = false; ReviveProgress = 0.0f; }
float UReviveComponent::GetDownedTimeRemaining() const { return FMath::Max(0.0f, MaxDownedTime - DownedTimer); }
float UReviveComponent::GetReviveProgress() const { return ReviveDuration > 0 ? ReviveProgress / ReviveDuration : 0.0f; }
