// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "TacticalSiegeGameMode.h"
ATacticalSiegeGameMode::ATacticalSiegeGameMode() { MaxPlayersPerTeam = 5; NumTeams = 2; MatchDuration = 180.0f; }
void ATacticalSiegeGameMode::StartMatch_Droper() { Super::StartMatch_Droper(); }
void ATacticalSiegeGameMode::OnBombPlanted() { /* Start bomb timer */ }
void ATacticalSiegeGameMode::OnBombDefused() { DefenderWins++; }
