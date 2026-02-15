// Copyright (c) 2026 mCompany. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DroperPlayerState.generated.h"

/**
 * ADroperPlayerState
 * 
 * Replicated per-player state: team, kills, deaths, extracted loot value,
 * operator selection, and match-specific stats.
 */
UCLASS()
class DROPER_API ADroperPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ADroperPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// --- Team ---
	UFUNCTION(BlueprintPure, Category = "Droper|PlayerState")
	int32 GetTeamId() const { return TeamId; }

	UFUNCTION(BlueprintCallable, Authority, Category = "Droper|PlayerState")
	void SetTeamId(int32 NewTeamId);

	// --- Combat Stats ---
	UFUNCTION(BlueprintCallable, Authority, Category = "Droper|PlayerState")
	void AddKill();

	UFUNCTION(BlueprintCallable, Authority, Category = "Droper|PlayerState")
	void AddDeath();

	UFUNCTION(BlueprintCallable, Authority, Category = "Droper|PlayerState")
	void AddAssist();

	UFUNCTION(BlueprintPure, Category = "Droper|PlayerState")
	int32 GetKills() const { return Kills; }

	UFUNCTION(BlueprintPure, Category = "Droper|PlayerState")
	int32 GetDeaths() const { return Deaths; }

	UFUNCTION(BlueprintPure, Category = "Droper|PlayerState")
	int32 GetAssists() const { return Assists; }

	UFUNCTION(BlueprintPure, Category = "Droper|PlayerState")
	float GetKDRatio() const { return Deaths > 0 ? (float)Kills / (float)Deaths : (float)Kills; }

	// --- Extraction (PvPvE) ---
	UFUNCTION(BlueprintCallable, Authority, Category = "Droper|PlayerState")
	void AddExtractedLootValue(int32 Value);

	UFUNCTION(BlueprintPure, Category = "Droper|PlayerState")
	int32 GetExtractedLootValue() const { return ExtractedLootValue; }

	UFUNCTION(BlueprintCallable, Authority, Category = "Droper|PlayerState")
	void SetSurvived(bool bSurvived);

	UFUNCTION(BlueprintPure, Category = "Droper|PlayerState")
	bool HasSurvived() const { return bSurvivedRaid; }

	// --- Operator ---
	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Droper|PlayerState")
	void Server_SelectOperator(const FName& OperatorId);

	UFUNCTION(BlueprintPure, Category = "Droper|PlayerState")
	FName GetSelectedOperator() const { return SelectedOperatorId; }

	// --- Damage Stats ---
	UFUNCTION(BlueprintCallable, Authority, Category = "Droper|PlayerState")
	void AddDamageDealt(float Amount);

	UFUNCTION(BlueprintPure, Category = "Droper|PlayerState")
	float GetDamageDealt() const { return DamageDealt; }

	// --- Delegates ---
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStatChanged, FName, StatName, int32, NewValue);
	UPROPERTY(BlueprintAssignable, Category = "Droper|PlayerState")
	FOnStatChanged OnStatChanged;

protected:
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Droper|PlayerState")
	int32 TeamId = INDEX_NONE;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Droper|PlayerState")
	int32 Kills = 0;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Droper|PlayerState")
	int32 Deaths = 0;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Droper|PlayerState")
	int32 Assists = 0;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Droper|PlayerState")
	int32 ExtractedLootValue = 0;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Droper|PlayerState")
	bool bSurvivedRaid = false;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Droper|PlayerState")
	FName SelectedOperatorId;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Droper|PlayerState")
	float DamageDealt = 0.0f;
};
