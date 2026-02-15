// Copyright (c) 2026 mCompany. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentTypes.generated.h"

UENUM(BlueprintType)
enum class EWeatherType : uint8
{
	Clear,
	Cloudy,
	LightRain,
	HeavyRain,
	Thunderstorm,
	Fog,
	Snow,
	Blizzard,
	Sandstorm
};

UENUM(BlueprintType)
enum class ETimeOfDay : uint8
{
	Dawn,
	Morning,
	Noon,
	Afternoon,
	Dusk,
	Night,
	Midnight
};

USTRUCT(BlueprintType)
struct DROPER_API FWindVector
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Direction = FVector(1.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 0.0f; // m/s

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GustIntensity = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GustFrequency = 0.0f;

	FVector GetWindVelocity() const { return Direction.GetSafeNormal() * Speed; }
};

USTRUCT(BlueprintType)
struct DROPER_API FSurfaceMaterial
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MaterialName; // "Concrete", "Wood", "Metal", "Glass", "Dirt", "Flesh"

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PenetrationResistance = 1.0f; // Multiplier

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RicochetProbability = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RicochetAngleThreshold = 15.0f; // Degrees from surface

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FootstepVolume = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDestructible = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DestructionThreshold = 100.0f;
};

USTRUCT(BlueprintType)
struct DROPER_API FWeatherTransition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeatherType FromWeather = EWeatherType::Clear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeatherType ToWeather = EWeatherType::Clear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TransitionDuration = 60.0f; // seconds

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Progress = 0.0f; // 0-1
};
