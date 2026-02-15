// Copyright (c) 2026 mCompany. All Rights Reserved.

#include "DroperGameStateBase.h"
#include "Net/UnrealNetwork.h"

ADroperGameStateBase::ADroperGameStateBase()
{
	TeamScores.Init(0, 2);
	NumTeams = 2;
}

void ADroperGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADroperGameStateBase, ReplicatedMatchPhase);
	DOREPLIFETIME(ADroperGameStateBase, MatchStartServerTime);
	DOREPLIFETIME(ADroperGameStateBase, TotalMatchDuration);
	DOREPLIFETIME(ADroperGameStateBase, TeamScores);
	DOREPLIFETIME(ADroperGameStateBase, NumTeams);
}

float ADroperGameStateBase::GetMatchElapsedTime() const
{
	if (ReplicatedMatchPhase == EDroperMatchPhase::Active || ReplicatedMatchPhase == EDroperMatchPhase::Overtime)
	{
		return GetServerWorldTimeSeconds() - MatchStartServerTime;
	}
	return 0.0f;
}

float ADroperGameStateBase::GetMatchRemainingTime() const
{
	const float Elapsed = GetMatchElapsedTime();
	return FMath::Max(0.0f, TotalMatchDuration - Elapsed);
}

int32 ADroperGameStateBase::GetTeamScore(int32 TeamId) const
{
	if (TeamScores.IsValidIndex(TeamId))
	{
		return TeamScores[TeamId];
	}
	return 0;
}

void ADroperGameStateBase::AddTeamScore(int32 TeamId, int32 Points)
{
	if (!HasAuthority()) return;

	if (TeamScores.IsValidIndex(TeamId))
	{
		TeamScores[TeamId] += Points;
		OnTeamScoreChanged.Broadcast(TeamId, TeamScores[TeamId]);
	}
}

int32 ADroperGameStateBase::GetAlivePlayerCount(int32 TeamId) const
{
	int32 Count = 0;
	for (const auto& PS : PlayerArray)
	{
		if (PS && !PS->IsInactive())
		{
			// If TeamId == -1, count all alive players
			if (TeamId < 0)
			{
				Count++;
			}
			// Otherwise filter by team — subclasses can add team-check logic
			else
			{
				Count++;
			}
		}
	}
	return Count;
}

void ADroperGameStateBase::SetMatchPhaseReplicated(EDroperMatchPhase NewPhase)
{
	if (!HasAuthority()) return;

	ReplicatedMatchPhase = NewPhase;

	if (NewPhase == EDroperMatchPhase::Active)
	{
		MatchStartServerTime = GetServerWorldTimeSeconds();
	}
}

void ADroperGameStateBase::SetMatchDuration(float Duration)
{
	if (HasAuthority())
	{
		TotalMatchDuration = Duration;
	}
}
