// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Types/WeaponTypes.h"
#include "WeaponDataAsset.generated.h"

UCLASS(BlueprintType)
class DROPER_API UWeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FName WeaponId;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FText DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FWeaponStats Stats;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FRecoilPattern Recoil;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TSoftObjectPtr<USkeletalMesh> WeaponMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TSoftClassPtr<AWeaponBase> WeaponClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TSoftObjectPtr<USoundBase> FireSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TSoftObjectPtr<USoundBase> ReloadSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<EAttachmentSlot> AvailableAttachmentSlots;
	virtual FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId("Weapon", WeaponId); }
};
