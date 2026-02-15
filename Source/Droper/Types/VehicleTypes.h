// Copyright (c) 2026 mCompany. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VehicleTypes.generated.h"

UENUM(BlueprintType)
enum class EVehicleType : uint8
{
	Wheeled,
	Tracked,
	Helicopter,
	Boat
};

UENUM(BlueprintType)
enum class ESeatPosition : uint8
{
	Driver,
	Gunner,
	Commander,
	PassengerFront,
	PassengerRear1,
	PassengerRear2,
	PassengerRear3,
	PassengerRear4
};

USTRUCT(BlueprintType)
struct DROPER_API FVehicleDamageZone
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ZoneName; // Engine, FrontArmor, RearArmor, LeftTrack, etc.

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentHP = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ArmorThickness = 10.0f; // mm

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDisabled = false;

	float GetHealthPercent() const { return MaxHP > 0 ? CurrentHP / MaxHP : 0.0f; }
};

USTRUCT(BlueprintType)
struct DROPER_API FVehicleSeatConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESeatPosition SeatType = ESeatPosition::Driver;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName AttachSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanUseWeapon = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasMountedGun = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ExitOffset = FVector(0, 200.0f, 0);
};
