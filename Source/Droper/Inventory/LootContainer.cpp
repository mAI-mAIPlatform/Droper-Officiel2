// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "LootContainer.h"
#include "Components/StaticMeshComponent.h"

ALootContainer::ALootContainer()
{
	bReplicates = true;
	ContainerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ContainerMesh"));
	SetRootComponent(ContainerMesh);
}

void ALootContainer::Open(AActor* Instigator) { bIsOpen = true; OnContainerOpened.Broadcast(Instigator); }
void ALootContainer::Close() { bIsOpen = false; }

bool ALootContainer::TakeItem(int32 Index, AActor* Taker)
{
	if (!Contents.IsValidIndex(Index)) return false;
	Contents.RemoveAt(Index);
	return true;
}

void ALootContainer::PopulateFromLootTable(const FLootTable& Table)
{
	Contents.Empty();
	for (const auto& Entry : Table.Entries)
	{
		if (Contents.Num() >= MaxItems) break;
		if (FMath::FRand() <= Entry.DropChance)
		{
			FInventorySlot Slot;
			Slot.ItemId = Entry.ItemId;
			Slot.CurrentStack = FMath::RandRange(Entry.MinQuantity, Entry.MaxQuantity);
			Contents.Add(Slot);
		}
	}
}
