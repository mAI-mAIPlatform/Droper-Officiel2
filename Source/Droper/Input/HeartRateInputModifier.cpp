// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "HeartRateInputModifier.h"
#include "EnhancedPlayerInput.h"
FInputActionValue UHeartRateInputModifier::ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime)
{
	// Would read heartbeat BPM from component and add sway — passthrough for now
	return CurrentValue;
}
