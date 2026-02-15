// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/InventoryTypes.h"
#include "CraftingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPER_API UCraftingComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UCraftingComponent();
	UFUNCTION(BlueprintCallable) bool StartCrafting(const FCraftingRecipe& Recipe, class UInventoryComponent* Inventory);
	UFUNCTION(BlueprintCallable) void CancelCrafting();
	UFUNCTION(BlueprintPure) bool IsCrafting() const { return bIsCrafting; }
	UFUNCTION(BlueprintPure) float GetCraftProgress() const;
	virtual void TickComponent(float DT, ELevelTick T, FActorComponentTickFunction* F) override;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCraftComplete, FName, ItemId);
	UPROPERTY(BlueprintAssignable) FOnCraftComplete OnCraftComplete;
protected:
	bool bIsCrafting = false;
	float CraftTimer = 0.0f;
	FCraftingRecipe ActiveRecipe;
	TWeakObjectPtr<class UInventoryComponent> BoundInventory;
};
