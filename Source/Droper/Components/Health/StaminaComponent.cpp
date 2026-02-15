// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "StaminaComponent.h"
UStaminaComponent::UStaminaComponent() { PrimaryComponentTick.bCanEverTick = true; }
void UStaminaComponent::TickComponent(float DT, ELevelTick T, FActorComponentTickFunction* F)
{
	Super::TickComponent(DT, T, F);
	TimeSinceLastDrain += DT;
	if (TimeSinceLastDrain >= RegenDelay && CurrentStamina < MaxStamina)
	{
		CurrentStamina = FMath::Min(MaxStamina, CurrentStamina + RegenRate * DT);
	}
}
void UStaminaComponent::DrainStamina(float Amount)
{
	CurrentStamina -= Amount * DrainMultiplier;
	TimeSinceLastDrain = 0.0f;
	if (CurrentStamina <= 0.0f) { CurrentStamina = 0.0f; OnStaminaDepleted.Broadcast(); }
}
