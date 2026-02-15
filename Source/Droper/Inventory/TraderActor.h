// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types/InventoryTypes.h"
#include "TraderActor.generated.h"

UCLASS(Blueprintable)
class DROPER_API ATraderActor : public AActor
{
	GENERATED_BODY()
public:
	ATraderActor();
	UFUNCTION(BlueprintCallable) bool BuyItem(int32 OfferIndex, class UInventoryComponent* Buyer, int32 CurrencyAmount);
	UFUNCTION(BlueprintCallable) bool SellItem(int32 InvIndex, class UInventoryComponent* Seller, float& OutEarnings);
	UFUNCTION(BlueprintPure) const TArray<FTraderOffer>& GetOffers() const { return Offers; }
	UFUNCTION(BlueprintCallable) void RefreshStock();
protected:
	UPROPERTY(EditAnywhere, Category="Trader") TArray<FTraderOffer> Offers;
	UPROPERTY(EditAnywhere, Category="Trader") float SellMultiplier = 0.5f;
	UPROPERTY(EditAnywhere, Category="Trader") float RestockInterval = 600.0f;
	FTimerHandle RestockTimer;
};
