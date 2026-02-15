// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "InventoryComponent.h"
#include "Net/UnrealNetwork.h"

UInventoryComponent::UInventoryComponent() { SetIsReplicatedByDefault(true); }

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& Out) const
{
	Super::GetLifetimeReplicatedProps(Out);
	DOREPLIFETIME(UInventoryComponent, Slots);
}

bool UInventoryComponent::AddItem(const FInventorySlot& Item)
{
	if (!HasSpaceForItem(Item)) return false;
	// Try stacking first
	for (int32 i = 0; i < Slots.Num(); i++)
	{
		if (Slots[i].ItemId == Item.ItemId && Slots[i].CurrentStack < Slots[i].MaxStack)
		{
			int32 Space = Slots[i].MaxStack - Slots[i].CurrentStack;
			int32 ToAdd = FMath::Min(Item.CurrentStack, Space);
			Slots[i].CurrentStack += ToAdd;
			OnItemAdded.Broadcast(Slots[i], i);
			OnInventoryChanged.Broadcast();
			return true;
		}
	}
	if (Slots.Num() >= MaxSlots) return false;
	int32 Idx = Slots.Add(Item);
	OnItemAdded.Broadcast(Item, Idx);
	OnInventoryChanged.Broadcast();
	return true;
}

bool UInventoryComponent::RemoveItem(int32 Index)
{
	if (!Slots.IsValidIndex(Index)) return false;
	FInventorySlot Removed = Slots[Index];
	Slots.RemoveAt(Index);
	OnItemRemoved.Broadcast(Removed, Index);
	OnInventoryChanged.Broadcast();
	return true;
}

bool UInventoryComponent::MoveItem(int32 From, int32 To)
{
	if (!Slots.IsValidIndex(From) || To < 0 || To >= MaxSlots) return false;
	if (To >= Slots.Num()) Slots.SetNum(To + 1);
	Slots.Swap(From, To);
	OnInventoryChanged.Broadcast();
	return true;
}

bool UInventoryComponent::StackItems(int32 Src, int32 Dst)
{
	if (!Slots.IsValidIndex(Src) || !Slots.IsValidIndex(Dst)) return false;
	if (Slots[Src].ItemId != Slots[Dst].ItemId) return false;
	int32 Space = Slots[Dst].MaxStack - Slots[Dst].CurrentStack;
	int32 Move = FMath::Min(Slots[Src].CurrentStack, Space);
	Slots[Dst].CurrentStack += Move;
	Slots[Src].CurrentStack -= Move;
	if (Slots[Src].CurrentStack <= 0) Slots.RemoveAt(Src);
	OnInventoryChanged.Broadcast();
	return true;
}

void UInventoryComponent::SortByCategory()
{
	Slots.Sort([](const FInventorySlot& A, const FInventorySlot& B) { return A.Category < B.Category; });
	OnInventoryChanged.Broadcast();
}

void UInventoryComponent::DropItem(int32 Index)
{
	if (!Slots.IsValidIndex(Index)) return;
	// Spawn pickup actor — stub
	RemoveItem(Index);
}

bool UInventoryComponent::IsSlotEmpty(int32 Index) const { return !Slots.IsValidIndex(Index) || Slots[Index].CurrentStack <= 0; }

const FInventorySlot& UInventoryComponent::GetSlot(int32 Index) const
{
	static FInventorySlot Empty;
	return Slots.IsValidIndex(Index) ? Slots[Index] : Empty;
}

int32 UInventoryComponent::FindItemByName(FName ItemId) const
{
	for (int32 i = 0; i < Slots.Num(); i++) { if (Slots[i].ItemId == ItemId) return i; }
	return INDEX_NONE;
}

float UInventoryComponent::GetTotalWeight() const
{
	float W = 0; for (const auto& S : Slots) W += S.Weight * S.CurrentStack; return W;
}

bool UInventoryComponent::HasSpaceForItem(const FInventorySlot& Item) const
{
	if (GetTotalWeight() + Item.Weight > MaxWeight) return false;
	// Check if stackable existing slot
	for (const auto& S : Slots) { if (S.ItemId == Item.ItemId && S.CurrentStack < S.MaxStack) return true; }
	return Slots.Num() < MaxSlots;
}
