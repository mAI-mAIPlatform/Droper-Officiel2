// Copyright (c) 2026 mCompany. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DroperGameInstance.generated.h"

class UDroperSaveGame;

/**
 * UDroperGameInstance
 * 
 * Global game instance persisting across map transitions.
 * Manages player profile, stash, subsystem initialization, and async level loading.
 */
UCLASS()
class DROPER_API UDroperGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UDroperGameInstance();

	virtual void Init() override;
	virtual void Shutdown() override;

	// --- Profile ---
	UFUNCTION(BlueprintCallable, Category = "Droper|Profile")
	void LoadPlayerProfile(const FString& PlayerId);

	UFUNCTION(BlueprintCallable, Category = "Droper|Profile")
	void SavePlayerProfile();

	UFUNCTION(BlueprintPure, Category = "Droper|Profile")
	bool IsProfileLoaded() const { return bProfileLoaded; }

	// --- Level Management ---
	UFUNCTION(BlueprintCallable, Category = "Droper|Level")
	void AsyncLoadLevel(const TSoftObjectPtr<UWorld>& LevelAsset, FName LevelInstanceName);

	UFUNCTION(BlueprintCallable, Category = "Droper|Level")
	void TravelToMap(const FString& MapURL, const FString& GameModeOverride = TEXT(""));

	// --- Matchmaking ---
	UFUNCTION(BlueprintCallable, Category = "Droper|Match")
	void FindMatch(const FString& GameModeId, const FString& Region);

	UFUNCTION(BlueprintCallable, Category = "Droper|Match")
	void CancelMatchSearch();

	// --- Delegates ---
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnProfileLoaded);
	UPROPERTY(BlueprintAssignable, Category = "Droper|Profile")
	FOnProfileLoaded OnProfileLoaded;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelLoaded, FName, LevelName);
	UPROPERTY(BlueprintAssignable, Category = "Droper|Level")
	FOnLevelLoaded OnLevelLoaded;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMatchFound, const FString&, SessionId);
	UPROPERTY(BlueprintAssignable, Category = "Droper|Match")
	FOnMatchFound OnMatchFound;

protected:
	UPROPERTY()
	TObjectPtr<UDroperSaveGame> CachedSaveGame;

	UPROPERTY()
	bool bProfileLoaded = false;

	UPROPERTY()
	FString CurrentPlayerId;

private:
	void OnAsyncLevelLoadComplete(const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result);
	void OnSessionSearchComplete(bool bWasSuccessful);
};
