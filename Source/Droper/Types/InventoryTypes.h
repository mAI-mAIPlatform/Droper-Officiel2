// Copyright (c) 2026 mCompany. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InventoryTypes.generated.h"

// =====================================================
// Item Rarity
// =====================================================

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	Common,
	Uncommon,
	Rare,
	Epic,
	Legendary,
	Unique
};

// =====================================================
// Item Category
// =====================================================

UENUM(BlueprintType)
enum class EItemCategory : uint8
{
	Weapon,
	Ammo,
	Armor,
	Medical,
	Gadget,
	Key,
	Barter,
	Backpack,
	Attachment,
	Consumable,
	Quest,
	Misc
};

// =====================================================
// Inventory Slot
// =====================================================

USTRUCT(BlueprintType)
struct DROPER_API FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StackCount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxStackSize = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Durability = 1.0f; // 0-1

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 GridX = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 GridY = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 GridWidth = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 GridHeight = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRotated = false;

	bool IsEmpty() const { return ItemId.IsNone(); }

	void Clear()
	{
		ItemId = NAME_None;
		StackCount = 0;
		Durability = 1.0f;
	}
};

// =====================================================
// Loot Table Row
// =====================================================

USTRUCT(BlueprintType)
struct DROPER_API FLootTableRow
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnWeight = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MinCount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxCount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemRarity MinRarity = EItemRarity::Common;
};

// =====================================================
// Trader Offer
// =====================================================

USTRUCT(BlueprintType)
struct DROPER_API FTraderOffer
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BuyPrice = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SellPrice = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RequiredTraderLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StockLimit = -1; // -1 = unlimited

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PriceMultiplier = 1.0f; // Dynamic economy
};

// =====================================================
// Crafting Recipe
// =====================================================

USTRUCT(BlueprintType)
struct DROPER_API FCraftingIngredient
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RequiredCount = 1;
};

USTRUCT(BlueprintType)
struct DROPER_API FCraftingRecipe
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName RecipeId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName OutputItemId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 OutputCount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCraftingIngredient> Ingredients;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CraftingTime = 5.0f; // seconds

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RequiredPlayerLevel = 1;
};
