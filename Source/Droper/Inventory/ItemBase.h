// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types/InventoryTypes.h"
#include "ItemBase.generated.h"

UCLASS(Abstract, Blueprintable)
class DROPER_API AItemBase : public AActor
{
	GENERATED_BODY()
public:
	AItemBase();
	UFUNCTION(BlueprintPure) FName GetItemId() const { return ItemData.ItemId; }
	UFUNCTION(BlueprintPure) const FInventorySlot& GetItemData() const { return ItemData; }
	UFUNCTION(BlueprintCallable) void SetItemData(const FInventorySlot& Data) { ItemData = Data; }
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item") FInventorySlot ItemData;
	UPROPERTY(VisibleAnywhere) TObjectPtr<UStaticMeshComponent> MeshComp;
};
