// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "DroperSpectatorController.h"

ADroperSpectatorController::ADroperSpectatorController() {}
void ADroperSpectatorController::SetupInputComponent() { Super::SetupInputComponent(); }
void ADroperSpectatorController::CycleNextTarget() { CurrentTargetIndex++; }
void ADroperSpectatorController::CyclePreviousTarget() { CurrentTargetIndex = FMath::Max(0, CurrentTargetIndex - 1); }
void ADroperSpectatorController::ToggleFreeCam() { bFreeCam = !bFreeCam; }
