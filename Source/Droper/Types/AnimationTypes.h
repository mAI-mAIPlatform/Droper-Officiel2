// Copyright (c) 2026 mCompany. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AnimationTypes.generated.h"

UENUM(BlueprintType)
enum class ELocomotionState : uint8
{
	Idle,
	Walking,
	Jogging,
	Sprinting,
	Crouching,
	CrouchWalking,
	Prone,
	ProneCrawling,
	Sliding,
	Vaulting,
	Climbing,
	Swimming,
	Falling,
	Landing
};

UENUM(BlueprintType)
enum class EWeaponPose : uint8
{
	Unarmed,
	Rifle_Ready,
	Rifle_Lowered,
	Rifle_ADS,
	Pistol_Ready,
	Pistol_ADS,
	Melee_Ready,
	Launcher_Ready,
	Mounted
};

UENUM(BlueprintType)
enum class EUpperBodyState : uint8
{
	None,
	Firing,
	Reloading,
	Equipping,
	Inspecting,
	Throwing,
	UsingItem,
	Healing,
	Breaching
};

USTRUCT(BlueprintType)
struct DROPER_API FProceduralRecoilData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentPitch = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentYaw = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentRoll = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector TranslationOffset = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RecoveryAlpha = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ShotsFiredInBurst = 0;

	void Reset()
	{
		CurrentPitch = CurrentYaw = CurrentRoll = 0.0f;
		TranslationOffset = FVector::ZeroVector;
		RecoveryAlpha = 0.0f;
		ShotsFiredInBurst = 0;
	}
};

USTRUCT(BlueprintType)
struct DROPER_API FLeanData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LeanAngle = 0.0f; // -1 to 1 (left/right)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LeanInterpSpeed = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxLeanAngle = 15.0f; // degrees

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector LeanOffset = FVector::ZeroVector;
};
