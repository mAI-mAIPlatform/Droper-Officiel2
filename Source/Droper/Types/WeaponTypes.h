// Copyright (c) 2026 mCompany. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "WeaponTypes.generated.h"

// =====================================================
// Weapon Slots
// =====================================================

UENUM(BlueprintType)
enum class EWeaponSlot : uint8
{
	Primary,
	Secondary,
	Sidearm,
	Melee,
	Gadget1,
	Gadget2,
	MAX UMETA(Hidden)
};

// =====================================================
// Fire Mode
// =====================================================

UENUM(BlueprintType)
enum class EFireMode : uint8
{
	Single,
	Burst,
	FullAuto
};

// =====================================================
// Weapon Category
// =====================================================

UENUM(BlueprintType)
enum class EWeaponCategory : uint8
{
	AssaultRifle,
	SMG,
	Shotgun,
	SniperRifle,
	DMR,
	Pistol,
	LMG,
	Launcher,
	MeleeWeapon
};

// =====================================================
// Ammo Caliber Tag
// =====================================================

UENUM(BlueprintType)
enum class EAmmoCaliber : uint8
{
	Cal_9x19,
	Cal_5_56x45,
	Cal_7_62x39,
	Cal_7_62x51,
	Cal_12_7x99,
	Cal_12Gauge,
	Cal_45ACP,
	Cal_5_7x28,
	Cal_338Lapua,
	Cal_40mmGrenade,
	Cal_RPG
};

// =====================================================
// Weapon Stats
// =====================================================

USTRUCT(BlueprintType)
struct DROPER_API FWeaponStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	EWeaponCategory Category = EWeaponCategory::AssaultRifle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float FireRate = 700.0f; // Rounds per minute

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float MuzzleVelocity = 900.0f; // m/s

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float BaseDamage = 35.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float BaseSpread = 1.0f; // MOA

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float ADSSpreadMultiplier = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float EffectiveRange = 400.0f; // meters

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float MaxRange = 800.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 MagazineSize = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 MaxReserveAmmo = 150;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	EAmmoCaliber AmmoType = EAmmoCaliber::Cal_5_56x45;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TArray<EFireMode> SupportedFireModes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float Weight = 3.5f; // kg

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float ADSSpeed = 0.25f; // seconds to ADS

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float EquipSpeed = 0.6f; // seconds to equip

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float ReloadSpeedTactical = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float ReloadSpeedEmpty = 2.8f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float HeadshotMultiplier = 4.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float ArmorPiercing = 0.3f; // 0-1
};

// =====================================================
// Recoil Pattern
// =====================================================

USTRUCT(BlueprintType)
struct DROPER_API FRecoilPattern
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float VerticalRecoilMin = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float VerticalRecoilMax = 0.6f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HorizontalRecoilMin = -0.15f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HorizontalRecoilMax = 0.15f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RecoilRecoverySpeed = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FirstShotMultiplier = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ADSRecoilMultiplier = 0.7f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CrouchRecoilMultiplier = 0.8f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProneRecoilMultiplier = 0.6f;

	// UCurveFloat for non-linear recoil over sustained fire
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UCurveFloat> VerticalRecoilCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UCurveFloat> HorizontalRecoilCurve;
};

// =====================================================
// Attachment Slot Types
// =====================================================

UENUM(BlueprintType)
enum class EAttachmentSlot : uint8
{
	Optic,
	Muzzle,
	Grip,
	Laser,
	Magazine,
	Stock,
	UnderBarrel
};

USTRUCT(BlueprintType)
struct DROPER_API FAttachmentModifiers
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpreadModifier = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RecoilModifier = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ADSSpeedModifier = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WeightModifier = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SoundReduction = 0.0f; // 0-1, suppressor

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MuzzleFlashReduction = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MagnificationOverride = 0.0f; // If > 0, sets optic zoom

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MagazineSizeOverride = 0; // If > 0, overrides mag size
};
