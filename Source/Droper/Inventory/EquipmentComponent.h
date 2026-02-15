// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/WeaponTypes.h"
#include "EquipmentComponent.generated.h"

class AWeaponBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWeaponEquipped, AWeaponBase*, Weapon, EWeaponSlot, Slot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWeaponUnequipped, AWeaponBase*, Weapon, EWeaponSlot, Slot);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPER_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UEquipmentComponent();
	UFUNCTION(BlueprintCallable) bool EquipWeapon(AWeaponBase* Weapon, EWeaponSlot Slot);
	UFUNCTION(BlueprintCallable) AWeaponBase* UnequipWeapon(EWeaponSlot Slot);
	UFUNCTION(BlueprintCallable) void SwitchToSlot(EWeaponSlot Slot);
	UFUNCTION(BlueprintCallable) void CycleWeapon(bool bForward);
	UFUNCTION(BlueprintPure) AWeaponBase* GetCurrentWeapon() const { return CurrentWeapon; }
	UFUNCTION(BlueprintPure) AWeaponBase* GetWeaponInSlot(EWeaponSlot Slot) const;
	UFUNCTION(BlueprintPure) EWeaponSlot GetCurrentSlot() const { return ActiveSlot; }

	UPROPERTY(BlueprintAssignable) FOnWeaponEquipped OnWeaponEquipped;
	UPROPERTY(BlueprintAssignable) FOnWeaponUnequipped OnWeaponUnequipped;
protected:
	UPROPERTY() TMap<EWeaponSlot, TObjectPtr<AWeaponBase>> WeaponSlots;
	UPROPERTY() TObjectPtr<AWeaponBase> CurrentWeapon;
	EWeaponSlot ActiveSlot = EWeaponSlot::Primary;
};
