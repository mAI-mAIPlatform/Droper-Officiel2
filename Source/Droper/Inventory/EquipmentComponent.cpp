// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "EquipmentComponent.h"
#include "Weapons/WeaponBase.h"

UEquipmentComponent::UEquipmentComponent() { PrimaryComponentTick.bCanEverTick = false; SetIsReplicatedByDefault(true); }

bool UEquipmentComponent::EquipWeapon(AWeaponBase* Weapon, EWeaponSlot Slot)
{
	if (!Weapon) return false;
	if (WeaponSlots.Contains(Slot)) UnequipWeapon(Slot);
	WeaponSlots.Add(Slot, Weapon);
	OnWeaponEquipped.Broadcast(Weapon, Slot);
	if (!CurrentWeapon) SwitchToSlot(Slot);
	return true;
}

AWeaponBase* UEquipmentComponent::UnequipWeapon(EWeaponSlot Slot)
{
	TObjectPtr<AWeaponBase>* Found = WeaponSlots.Find(Slot);
	if (!Found) return nullptr;
	AWeaponBase* Weapon = *Found;
	WeaponSlots.Remove(Slot);
	OnWeaponUnequipped.Broadcast(Weapon, Slot);
	if (CurrentWeapon == Weapon) CurrentWeapon = nullptr;
	return Weapon;
}

void UEquipmentComponent::SwitchToSlot(EWeaponSlot Slot)
{
	AWeaponBase* Weapon = GetWeaponInSlot(Slot);
	if (Weapon) { CurrentWeapon = Weapon; ActiveSlot = Slot; }
}

void UEquipmentComponent::CycleWeapon(bool bForward)
{
	int32 Current = static_cast<int32>(ActiveSlot);
	int32 Max = static_cast<int32>(EWeaponSlot::Sidearm);
	for (int32 i = 1; i <= Max; i++)
	{
		int32 Next = bForward ? (Current + i) % (Max + 1) : (Current - i + Max + 1) % (Max + 1);
		EWeaponSlot NextSlot = static_cast<EWeaponSlot>(Next);
		if (WeaponSlots.Contains(NextSlot)) { SwitchToSlot(NextSlot); return; }
	}
}

AWeaponBase* UEquipmentComponent::GetWeaponInSlot(EWeaponSlot Slot) const
{
	const TObjectPtr<AWeaponBase>* Found = WeaponSlots.Find(Slot);
	return Found ? *Found : nullptr;
}
