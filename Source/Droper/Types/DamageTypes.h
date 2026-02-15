// Copyright (c) 2026 mCompany. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DamageTypes.generated.h"

// =====================================================
// Body Part Zones (8-zone localized system)
// =====================================================

UENUM(BlueprintType)
enum class EBodyPart : uint8
{
	Head,
	Neck,
	UpperTorso,
	LowerTorso,
	LeftArm,
	RightArm,
	LeftLeg,
	RightLeg
};

// =====================================================
// Critical States (bitflag-compatible)
// =====================================================

UENUM(BlueprintType, Meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class ECriticalState : uint8
{
	None			= 0		UMETA(Hidden),
	Hemorrhage		= 1 << 0,
	Fracture		= 1 << 1,
	Concussion		= 1 << 2,
	Unconscious		= 1 << 3,
	Blinded			= 1 << 4,
	Deafened		= 1 << 5,
	PainShock		= 1 << 6
};
ENUM_CLASS_FLAGS(ECriticalState);

// =====================================================
// Body Part Health Data
// =====================================================

USTRUCT(BlueprintType)
struct DROPER_API FBodyPartHealth
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentHP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ArmorModifier = 0.0f; // 0.0 = no armor, 1.0 = full absorption

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 ActiveCriticalStates = 0; // Bitmask of ECriticalState

	bool HasCriticalState(ECriticalState State) const
	{
		return (ActiveCriticalStates & static_cast<uint8>(State)) != 0;
	}

	void AddCriticalState(ECriticalState State)
	{
		ActiveCriticalStates |= static_cast<uint8>(State);
	}

	void RemoveCriticalState(ECriticalState State)
	{
		ActiveCriticalStates &= ~static_cast<uint8>(State);
	}

	float GetHealthPercent() const
	{
		return MaxHP > 0.0f ? CurrentHP / MaxHP : 0.0f;
	}

	bool IsDestroyed() const { return CurrentHP <= 0.0f; }
};

// =====================================================
// Localized Damage Event
// =====================================================

USTRUCT(BlueprintType)
struct DROPER_API FLocalizedDamageEvent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBodyPart TargetBodyPart = EBodyPart::UpperTorso;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RawDamage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PenetrationDepth = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ArmorPierce = 0.0f; // 0-1, how much armor this bypasses

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ImpulseDirection = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector HitLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DistanceFromMuzzle = 0.0f;

	UPROPERTY()
	TWeakObjectPtr<AActor> Instigator;

	UPROPERTY()
	TWeakObjectPtr<AActor> DamageCauser;

	// Probability to trigger critical state
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HemorrhageChance = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FractureChance = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ConcussionChance = 0.0f;
};

// =====================================================
// Damage Type Tags
// =====================================================

UENUM(BlueprintType)
enum class EDamageCategory : uint8
{
	Ballistic,
	Explosive,
	Melee,
	Fire,
	Fall,
	Drowning,
	Bleeding,
	Environmental
};
