// Copyright (c) 2026 mCompany. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NetworkTypes.generated.h"

UENUM(BlueprintType)
enum class EConnectionQuality : uint8
{
	Excellent,	// < 30ms
	Good,		// 30-60ms
	Fair,		// 60-100ms
	Poor,		// 100-200ms
	Critical	// > 200ms
};

USTRUCT(BlueprintType)
struct DROPER_API FServerInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ServerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MapName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString GameMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Region;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentPlayers = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxPlayers = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Ping = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsLocked = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SessionId;
};

USTRUCT(BlueprintType)
struct DROPER_API FNetworkStats
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	float RTT = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	float PacketLoss = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	float InBytesPerSec = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	float OutBytesPerSec = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	EConnectionQuality Quality = EConnectionQuality::Good;

	void UpdateQuality()
	{
		if (RTT < 30.0f) Quality = EConnectionQuality::Excellent;
		else if (RTT < 60.0f) Quality = EConnectionQuality::Good;
		else if (RTT < 100.0f) Quality = EConnectionQuality::Fair;
		else if (RTT < 200.0f) Quality = EConnectionQuality::Poor;
		else Quality = EConnectionQuality::Critical;
	}
};
