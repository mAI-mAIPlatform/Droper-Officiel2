// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Types/InventoryTypes.h"
#include "DroperSaveGame.generated.h"

UCLASS()
class DROPER_API UDroperSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(SaveGame) FString PlayerName;
	UPROPERTY(SaveGame) int32 PlayerLevel = 1;
	UPROPERTY(SaveGame) int32 XP = 0;
	UPROPERTY(SaveGame) int32 Currency = 0;
	UPROPERTY(SaveGame) TArray<FInventorySlot> StashItems;
	UPROPERTY(SaveGame) TMap<FName, bool> UnlockedItems;
	UPROPERTY(SaveGame) TMap<FName, int32> QuestProgress;
	UPROPERTY(SaveGame) float MasterVolume = 1.0f;
	UPROPERTY(SaveGame) float SFXVolume = 1.0f;
	UPROPERTY(SaveGame) float MouseSensitivity = 1.0f;
	UPROPERTY(SaveGame) int32 TotalKills = 0;
	UPROPERTY(SaveGame) int32 TotalDeaths = 0;
	UPROPERTY(SaveGame) int32 TotalExtractions = 0;
	UPROPERTY(SaveGame) float TotalPlayTime = 0.0f;
};
