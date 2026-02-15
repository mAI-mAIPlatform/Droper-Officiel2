// Copyright (c) 2026 mCompany. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DroperCoreTypes.generated.h"

// =====================================================
// Match & Session
// =====================================================

UENUM(BlueprintType)
enum class EMatchPhase : uint8
{
	None,
	Lobby,
	OperatorSelect,
	Deploying,
	InProgress,
	Overtime,
	PostMatch,
	Travelling
};

UENUM(BlueprintType)
enum class ETeamId : uint8
{
	NoTeam		= 0,
	TeamAlpha	= 1,
	TeamBravo	= 2,
	TeamCharlie = 3,
	TeamDelta	= 4
};

UENUM(BlueprintType)
enum class EGameModeType : uint8
{
	Extraction,
	TacticalSiege,
	FieldWar
};

// =====================================================
// Player Loadout
// =====================================================

USTRUCT(BlueprintType)
struct DROPER_API FPlayerLoadout
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName PrimaryWeaponId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SecondaryWeaponId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SidearmId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MeleeId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> GadgetIds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ArmorId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName BackpackId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName OperatorId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer CosmeticTags;
};

// =====================================================
// Currency & Economy
// =====================================================

UENUM(BlueprintType)
enum class ECurrencyType : uint8
{
	Roubles,
	Dollars,
	PremiumTokens
};

USTRUCT(BlueprintType)
struct DROPER_API FWalletEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECurrencyType CurrencyType = ECurrencyType::Roubles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 Amount = 0;
};

// =====================================================
// Region & Matchmaking
// =====================================================

USTRUCT(BlueprintType)
struct DROPER_API FMatchSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGameModeType GameMode = EGameModeType::Extraction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MapId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Region;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxPlayers = 12;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAllowBackfill = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bNightTimeForced = false;
};
