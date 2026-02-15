// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "TraderActor.h"
#include "InventoryComponent.h"

ATraderActor::ATraderActor() { PrimaryActorTick.bCanEverTick = false; }

bool ATraderActor::BuyItem(int32 OfferIndex, UInventoryComponent* Buyer, int32 CurrencyAmount)
{
	if (!Buyer || !Offers.IsValidIndex(OfferIndex)) return false;
	const FTraderOffer& Offer = Offers[OfferIndex];
	if (CurrencyAmount < Offer.Price || Offer.Stock <= 0) return false;
	FInventorySlot Slot; Slot.ItemId = Offer.ItemId;
	if (!Buyer->AddItem(Slot)) return false;
	Offers[OfferIndex].Stock--;
	return true;
}

bool ATraderActor::SellItem(int32 InvIndex, UInventoryComponent* Seller, float& OutEarnings)
{
	if (!Seller) return false;
	const FInventorySlot& Slot = Seller->GetSlot(InvIndex);
	if (Slot.ItemId.IsNone()) return false;
	OutEarnings = Slot.BaseValue * SellMultiplier;
	Seller->RemoveItem(InvIndex);
	return true;
}

void ATraderActor::RefreshStock()
{
	for (auto& Offer : Offers) { Offer.Stock = Offer.MaxStock; }
}
