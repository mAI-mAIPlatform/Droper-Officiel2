// Copyright (c) 2026 mCompany. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DroperGameModeBase.generated.h"

class ADroperCharacterBase;
class ADroperPlayerController;

/**
 * ADroperGameModeBase
 *
 * Abstract base game mode defining core match flow:
 * Warmup → Active → Overtime → PostMatch.
 */
UENUM(BlueprintType)
enum class EDroperMatchPhase : uint8
{
	WaitingForPlayers,
	Warmup,
	Active,
	Overtime,
	PostMatch,
	TravellingToMap
};

UCLASS(Abstract)
class DROPER_API ADroperGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADroperGameModeBase();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer);

	// --- Match Flow ---
	UFUNCTION(BlueprintCallable, Category = "Droper|Match")
	void SetMatchPhase(EDroperMatchPhase NewPhase);

	UFUNCTION(BlueprintPure, Category = "Droper|Match")
	EDroperMatchPhase GetMatchPhase() const { return CurrentMatchPhase; }

	UFUNCTION(BlueprintCallable, Category = "Droper|Match")
	void StartWarmup();

	UFUNCTION(BlueprintCallable, Category = "Droper|Match")
	void StartMatch_Droper();

	UFUNCTION(BlueprintCallable, Category = "Droper|Match")
	void EndMatch(const FString& Reason);

	// --- Spawn ---
	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	// --- Team ---
	UFUNCTION(BlueprintCallable, Category = "Droper|Team")
	virtual int32 AssignTeam(APlayerController* Player);

	// --- Delegates ---
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMatchPhaseChanged, EDroperMatchPhase, NewPhase);
	UPROPERTY(BlueprintAssignable, Category = "Droper|Match")
	FOnMatchPhaseChanged OnMatchPhaseChanged;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerJoined, APlayerController*, Player);
	UPROPERTY(BlueprintAssignable, Category = "Droper|Match")
	FOnPlayerJoined OnPlayerJoined;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerLeft, APlayerController*, Player);
	UPROPERTY(BlueprintAssignable, Category = "Droper|Match")
	FOnPlayerLeft OnPlayerLeft;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Match")
	float WarmupDuration = 30.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Match")
	float MatchDuration = 1200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Match")
	int32 MaxPlayers = 12;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Match")
	int32 MaxTeams = 2;

	UPROPERTY(BlueprintReadOnly, Category = "Droper|Match")
	EDroperMatchPhase CurrentMatchPhase = EDroperMatchPhase::WaitingForPlayers;

	UPROPERTY()
	TArray<TObjectPtr<APlayerController>> ConnectedPlayers;

	FTimerHandle WarmupTimerHandle;
	FTimerHandle MatchTimerHandle;

	virtual void OnWarmupEnd();
	virtual void OnMatchTimeExpired();
};
