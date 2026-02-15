// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "CraftingComponent.h"
#include "InventoryComponent.h"

UCraftingComponent::UCraftingComponent() { PrimaryComponentTick.bCanEverTick = true; }

bool UCraftingComponent::StartCrafting(const FCraftingRecipe& Recipe, UInventoryComponent* Inventory)
{
	if (bIsCrafting || !Inventory) return false;
	// Verify ingredients
	for (const auto& Ing : Recipe.Ingredients)
	{
		int32 Idx = Inventory->FindItemByName(Ing.Key);
		if (Idx == INDEX_NONE) return false;
		if (Inventory->GetSlot(Idx).CurrentStack < Ing.Value) return false;
	}
	// Consume ingredients
	for (const auto& Ing : Recipe.Ingredients) { int32 Idx = Inventory->FindItemByName(Ing.Key); Inventory->RemoveItem(Idx); }
	ActiveRecipe = Recipe;
	BoundInventory = Inventory;
	bIsCrafting = true;
	CraftTimer = 0.0f;
	return true;
}

void UCraftingComponent::CancelCrafting() { bIsCrafting = false; CraftTimer = 0.0f; }

float UCraftingComponent::GetCraftProgress() const { return ActiveRecipe.CraftTime > 0 ? CraftTimer / ActiveRecipe.CraftTime : 0.0f; }

void UCraftingComponent::TickComponent(float DT, ELevelTick T, FActorComponentTickFunction* F)
{
	Super::TickComponent(DT, T, F);
	if (!bIsCrafting) return;
	CraftTimer += DT;
	if (CraftTimer >= ActiveRecipe.CraftTime)
	{
		bIsCrafting = false;
		if (BoundInventory.IsValid())
		{
			FInventorySlot Result; Result.ItemId = ActiveRecipe.ResultItemId;
			BoundInventory->AddItem(Result);
		}
		OnCraftComplete.Broadcast(ActiveRecipe.ResultItemId);
	}
}
