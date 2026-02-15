// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types/InventoryTypes.h"
#include "LootContainer.generated.h"

UCLASS(Blueprintable)
class DROPER_API ALootContainer : public AActor
{
	GENERATED_BODY()
public:
	ALootContainer();
	UFUNCTION(BlueprintCallable) void Open(AActor* Instigator);
	UFUNCTION(BlueprintCallable) void Close();
	UFUNCTION(BlueprintPure) bool IsOpen() const { return bIsOpen; }
	UFUNCTION(BlueprintPure) const TArray<FInventorySlot>& GetContents() const { return Contents; }
	UFUNCTION(BlueprintCallable) bool TakeItem(int32 Index, AActor* Taker);
	UFUNCTION(BlueprintCallable) void PopulateFromLootTable(const FLootTable& Table);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnContainerOpened, AActor*, Opener);
	UPROPERTY(BlueprintAssignable) FOnContainerOpened OnContainerOpened;
protected:
	UPROPERTY(EditAnywhere, Category="Loot") TArray<FInventorySlot> Contents;
	UPROPERTY(EditAnywhere) int32 MaxItems = 8;
	bool bIsOpen = false;
	UPROPERTY(VisibleAnywhere) TObjectPtr<UStaticMeshComponent> ContainerMesh;
};
