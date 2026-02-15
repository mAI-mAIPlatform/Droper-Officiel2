// Copyright (c) 2026 mCompany. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DroperGameModeBase.h"
#include "DroperGameStateBase.generated.h"

/**
 * ADroperGameStateBase
 *
 * Replicated match state: clock, phase, team scores, connected player count.
 */
UCLASS()
class DROPER_API ADroperGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	ADroperGameStateBase();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// --- Match Clock ---
	UFUNCTION(BlueprintPure, Category = "Droper|State")
	float GetMatchElapsedTime() const;

	UFUNCTION(BlueprintPure, Category = "Droper|State")
	float GetMatchRemainingTime() const;

	UFUNCTION(BlueprintPure, Category = "Droper|State")
	EDroperMatchPhase GetCurrentPhase() const { return ReplicatedMatchPhase; }

	// --- Teams ---
	UFUNCTION(BlueprintPure, Category = "Droper|State")
	int32 GetTeamScore(int32 TeamId) const;

	UFUNCTION(BlueprintCallable, Authority, Category = "Droper|State")
	void AddTeamScore(int32 TeamId, int32 Points);

	UFUNCTION(BlueprintPure, Category = "Droper|State")
	int32 GetAlivePlayerCount(int32 TeamId = -1) const;

	// --- Server-Side Setters ---
	void SetMatchPhaseReplicated(EDroperMatchPhase NewPhase);
	void SetMatchDuration(float Duration);

	// --- Delegates ---
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTeamScoreChanged, int32, TeamId, int32, NewScore);
	UPROPERTY(BlueprintAssignable, Category = "Droper|State")
	FOnTeamScoreChanged OnTeamScoreChanged;

protected:
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Droper|State")
	EDroperMatchPhase ReplicatedMatchPhase = EDroperMatchPhase::WaitingForPlayers;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Droper|State")
	float MatchStartServerTime = 0.0f;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Droper|State")
	float TotalMatchDuration = 1200.0f;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Droper|State")
	TArray<int32> TeamScores;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Droper|State")
	int32 NumTeams = 2;
};
