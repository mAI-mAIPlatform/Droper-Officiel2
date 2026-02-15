// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "FieldWarGameMode.h"
AFieldWarGameMode::AFieldWarGameMode() { MaxPlayersPerTeam = 32; NumTeams = 2; MatchDuration = 1800.0f; }
void AFieldWarGameMode::StartMatch_Droper() { Super::StartMatch_Droper(); for (int32 i = 0; i < NumTeams; i++) TeamTickets.Add(i, TicketsPerTeam); }
void AFieldWarGameMode::OnObjectiveCaptured(int32 TeamId, int32 Idx) { /* Ticket drain for losing team */ }
