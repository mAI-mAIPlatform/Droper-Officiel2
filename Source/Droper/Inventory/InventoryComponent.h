// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/InventoryTypes.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemAdded, const FInventorySlot&, Slot, int32, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemRemoved, const FInventorySlot&, Slot, int32, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPER_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UInventoryComponent();

	UFUNCTION(BlueprintCallable) bool AddItem(const FInventorySlot& Item);
	UFUNCTION(BlueprintCallable) bool RemoveItem(int32 Index);
	UFUNCTION(BlueprintCallable) bool MoveItem(int32 FromIndex, int32 ToIndex);
	UFUNCTION(BlueprintCallable) bool StackItems(int32 SourceIndex, int32 TargetIndex);
	UFUNCTION(BlueprintCallable) void SortByCategory();
	UFUNCTION(BlueprintCallable) void DropItem(int32 Index);

	UFUNCTION(BlueprintPure) int32 GetItemCount() const { return Slots.Num(); }
	UFUNCTION(BlueprintPure) bool IsSlotEmpty(int32 Index) const;
	UFUNCTION(BlueprintPure) const FInventorySlot& GetSlot(int32 Index) const;
	UFUNCTION(BlueprintPure) int32 FindItemByName(FName ItemId) const;
	UFUNCTION(BlueprintPure) float GetTotalWeight() const;
	UFUNCTION(BlueprintPure) bool HasSpaceForItem(const FInventorySlot& Item) const;

	UPROPERTY(BlueprintAssignable) FOnItemAdded OnItemAdded;
	UPROPERTY(BlueprintAssignable) FOnItemRemoved OnItemRemoved;
	UPROPERTY(BlueprintAssignable) FOnInventoryChanged OnInventoryChanged;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory") int32 MaxSlots = 20;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory") float MaxWeight = 50.0f;
	UPROPERTY(Replicated) TArray<FInventorySlot> Slots;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
