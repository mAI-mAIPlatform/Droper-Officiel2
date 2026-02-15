// Copyright (c) 2026 mCompany. All Rights Reserved.

#include "DroperGameInstance.h"
#include "Droper.h"
#include "Persistence/DroperSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

UDroperGameInstance::UDroperGameInstance()
{
	CachedSaveGame = nullptr;
	bProfileLoaded = false;
}

void UDroperGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogDroper, Log, TEXT("DroperGameInstance initialized"));
}

void UDroperGameInstance::Shutdown()
{
	if (bProfileLoaded)
	{
		SavePlayerProfile();
	}
	Super::Shutdown();
}

// --------------------------------------------------
// Profile Management
// --------------------------------------------------

void UDroperGameInstance::LoadPlayerProfile(const FString& PlayerId)
{
	CurrentPlayerId = PlayerId;
	const FString SlotName = FString::Printf(TEXT("DroperProfile_%s"), *PlayerId);

	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		CachedSaveGame = Cast<UDroperSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	}
	else
	{
		CachedSaveGame = Cast<UDroperSaveGame>(
			UGameplayStatics::CreateSaveGameObject(UDroperSaveGame::StaticClass())
		);
	}

	bProfileLoaded = (CachedSaveGame != nullptr);

	if (bProfileLoaded)
	{
		OnProfileLoaded.Broadcast();
		UE_LOG(LogDroper, Log, TEXT("Profile loaded for player: %s"), *PlayerId);
	}
	else
	{
		UE_LOG(LogDroper, Error, TEXT("Failed to load profile for player: %s"), *PlayerId);
	}
}

void UDroperGameInstance::SavePlayerProfile()
{
	if (!CachedSaveGame || CurrentPlayerId.IsEmpty())
	{
		return;
	}

	const FString SlotName = FString::Printf(TEXT("DroperProfile_%s"), *CurrentPlayerId);
	UGameplayStatics::SaveGameToSlot(CachedSaveGame, SlotName, 0);
	UE_LOG(LogDroper, Log, TEXT("Profile saved for player: %s"), *CurrentPlayerId);
}

// --------------------------------------------------
// Level Management
// --------------------------------------------------

void UDroperGameInstance::AsyncLoadLevel(const TSoftObjectPtr<UWorld>& LevelAsset, FName LevelInstanceName)
{
	if (LevelAsset.IsNull())
	{
		UE_LOG(LogDroper, Warning, TEXT("AsyncLoadLevel: Null level asset provided"));
		return;
	}

	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	StreamableManager.RequestAsyncLoad(
		LevelAsset.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda([this, LevelInstanceName]()
		{
			UE_LOG(LogDroper, Log, TEXT("Level async load complete: %s"), *LevelInstanceName.ToString());
			OnLevelLoaded.Broadcast(LevelInstanceName);
		})
	);
}

void UDroperGameInstance::TravelToMap(const FString& MapURL, const FString& GameModeOverride)
{
	FString TravelURL = MapURL;
	if (!GameModeOverride.IsEmpty())
	{
		TravelURL += FString::Printf(TEXT("?game=%s"), *GameModeOverride);
	}

	UWorld* World = GetWorld();
	if (World)
	{
		World->ServerTravel(TravelURL);
	}
}

// --------------------------------------------------
// Matchmaking
// --------------------------------------------------

void UDroperGameInstance::FindMatch(const FString& GameModeId, const FString& Region)
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (!OnlineSub)
	{
		UE_LOG(LogDroper, Warning, TEXT("No OnlineSubsystem available for matchmaking"));
		return;
	}

	UE_LOG(LogDroper, Log, TEXT("Searching for match: Mode=%s, Region=%s"), *GameModeId, *Region);
	// Session search would be implemented here via OnlineSub->GetSessionInterface()
}

void UDroperGameInstance::CancelMatchSearch()
{
	UE_LOG(LogDroper, Log, TEXT("Match search cancelled"));
}

void UDroperGameInstance::OnAsyncLevelLoadComplete(const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result)
{
	if (Result == EAsyncLoadingResult::Succeeded)
	{
		UE_LOG(LogDroper, Log, TEXT("Async level load succeeded: %s"), *PackageName.ToString());
	}
	else
	{
		UE_LOG(LogDroper, Error, TEXT("Async level load failed: %s"), *PackageName.ToString());
	}
}

void UDroperGameInstance::OnSessionSearchComplete(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UE_LOG(LogDroper, Log, TEXT("Session search succeeded"));
	}
}
