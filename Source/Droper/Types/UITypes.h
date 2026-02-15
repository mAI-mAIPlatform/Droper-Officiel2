// Copyright (c) 2026 mCompany. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UITypes.generated.h"

UENUM(BlueprintType)
enum class EMenuState : uint8
{
	None,
	MainMenu,
	Lobby,
	LoadoutSelect,
	OperatorSelect,
	Settings,
	Stash,
	Traders,
	InGame,
	PauseMenu,
	GameOver,
	Scoreboard
};

UENUM(BlueprintType)
enum class EHUDElement : uint8
{
	Crosshair,
	HealthBody,
	AmmoCounter,
	StaminaBar,
	Minimap,
	Compass,
	KillFeed,
	InteractionPrompt,
	DamageIndicator,
	SquadInfo,
	ExtractionTimer,
	VoIPIndicator,
	Notifications,
	Chat,
	PingMarker
};

USTRUCT(BlueprintType)
struct DROPER_API FNotificationData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Message;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor Color = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bPlaySound = true;
};

USTRUCT(BlueprintType)
struct DROPER_API FCrosshairProfile
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor Color = FLinearColor(0.0f, 1.0f, 0.0f, 0.8f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Size = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Thickness = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Gap = 4.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShowDot = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DynamicSpreadScale = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor HitConfirmColor = FLinearColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor HeadshotColor = FLinearColor(1.0f, 0.8f, 0.0f, 1.0f);
};

USTRUCT(BlueprintType)
struct DROPER_API FKillFeedEntry
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString KillerName;

	UPROPERTY(BlueprintReadOnly)
	FString VictimName;

	UPROPERTY(BlueprintReadOnly)
	FName WeaponId;

	UPROPERTY(BlueprintReadOnly)
	bool bHeadshot = false;

	UPROPERTY(BlueprintReadOnly)
	float Timestamp = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	int32 KillerTeam = INDEX_NONE;

	UPROPERTY(BlueprintReadOnly)
	int32 VictimTeam = INDEX_NONE;
};
