// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/InventoryTypes.h"
#include "StashComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPER_API UStashComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UStashComponent();
	UFUNCTION(BlueprintCallable) bool AddToStash(const FInventorySlot& Item);
	UFUNCTION(BlueprintCallable) bool RemoveFromStash(int32 Index);
	UFUNCTION(BlueprintCallable) void TransferToInventory(int32 StashIndex, class UInventoryComponent* Inventory);
	UFUNCTION(BlueprintCallable) void TransferFromInventory(int32 InvIndex, class UInventoryComponent* Inventory);
	UFUNCTION(BlueprintPure) const TArray<FInventorySlot>& GetStashContents() const { return StashSlots; }
	UFUNCTION(BlueprintCallable) void LoadStash(const TArray<FInventorySlot>& Data) { StashSlots = Data; }
	UFUNCTION(BlueprintPure) int32 GetStashSize() const { return StashSlots.Num(); }
protected:
	UPROPERTY(EditAnywhere) int32 MaxStashSlots = 100;
	UPROPERTY(SaveGame) TArray<FInventorySlot> StashSlots;
};
