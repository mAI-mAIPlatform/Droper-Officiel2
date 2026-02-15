// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "StashComponent.h"
#include "InventoryComponent.h"

UStashComponent::UStashComponent() { PrimaryComponentTick.bCanEverTick = false; }

bool UStashComponent::AddToStash(const FInventorySlot& Item)
{
	if (StashSlots.Num() >= MaxStashSlots) return false;
	StashSlots.Add(Item);
	return true;
}

bool UStashComponent::RemoveFromStash(int32 Index)
{
	if (!StashSlots.IsValidIndex(Index)) return false;
	StashSlots.RemoveAt(Index);
	return true;
}

void UStashComponent::TransferToInventory(int32 StashIndex, UInventoryComponent* Inventory)
{
	if (!Inventory || !StashSlots.IsValidIndex(StashIndex)) return;
	if (Inventory->AddItem(StashSlots[StashIndex])) StashSlots.RemoveAt(StashIndex);
}

void UStashComponent::TransferFromInventory(int32 InvIndex, UInventoryComponent* Inventory)
{
	if (!Inventory) return;
	const FInventorySlot& Slot = Inventory->GetSlot(InvIndex);
	if (AddToStash(Slot)) Inventory->RemoveItem(InvIndex);
}
