// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "ExtractionGameMode.h"
AExtractionGameMode::AExtractionGameMode() { MatchDuration = RaidDuration; MaxPlayersPerTeam = 4; }
void AExtractionGameMode::StartMatch_Droper() { Super::StartMatch_Droper(); GetWorldTimerManager().SetTimer(ExtractionActivationTimer, this, &AExtractionGameMode::ActivateExtractionPoints, ExtractionActivationTime); }
void AExtractionGameMode::EndMatch() { Super::EndMatch(); }
void AExtractionGameMode::OnPlayerExtracted(AController* Player) { /* Save loot, mark extracted */ }
void AExtractionGameMode::ActivateExtractionPoints() { /* Find all AExtractionPoint and activate */ }
