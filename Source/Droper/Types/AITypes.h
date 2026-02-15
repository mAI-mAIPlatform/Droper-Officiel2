// Copyright (c) 2026 mCompany. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AITypes.generated.h"

UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,
	Patrolling,
	Alert,
	Investigating,
	Engaging,
	Flanking,
	Retreating,
	Healing,
	Downed,
	Dead
};

UENUM(BlueprintType)
enum class EThreatLevel : uint8
{
	None,
	Low,
	Medium,
	High,
	Critical
};

UENUM(BlueprintType)
enum class EBehaviorProfile : uint8
{
	Aggressive,
	Defensive,
	Tactical,
	Sniper,
	Support,
	Patrol,
	Boss
};

UENUM(BlueprintType)
enum class ESquadRole : uint8
{
	Leader,
	Pointman,
	Rifleman,
	Support,
	Marksman,
	Medic,
	Breacher
};

USTRUCT(BlueprintType)
struct DROPER_API FSquadOrder
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName OrderType; // "Hold", "Advance", "Flank", "Fallback", "Breach"

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector TargetLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TWeakObjectPtr<AActor> TargetActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Priority = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Timeout = 30.0f;
};

USTRUCT(BlueprintType)
struct DROPER_API FAIAccuracyProfile
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseAccuracy = 0.7f; // 0-1

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReactionTimeMin = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReactionTimeMax = 0.8f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BurstLengthMin = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BurstLengthMax = 8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SuppressionEffectiveness = 0.5f; // How much getting shot at degrades aim
};
