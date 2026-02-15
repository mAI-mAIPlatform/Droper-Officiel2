// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types/WeaponTypes.h"
#include "WeaponBase.generated.h"

class USkeletalMeshComponent;
class UWeaponRecoilComponent;
class UWeaponSwayComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFired);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReloadComplete);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAmmoChanged, int32, CurrentAmmo);

UCLASS(Abstract, Blueprintable)
class DROPER_API AWeaponBase : public AActor
{
	GENERATED_BODY()
public:
	AWeaponBase();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// --- Actions ---
	UFUNCTION(BlueprintCallable) virtual void StartFire();
	UFUNCTION(BlueprintCallable) virtual void StopFire();
	UFUNCTION(BlueprintCallable) virtual void Reload();
	UFUNCTION(BlueprintCallable) void CancelReload();
	UFUNCTION(BlueprintCallable) void SwitchFireMode();
	UFUNCTION(BlueprintCallable) void SetADS(bool bAiming);

	// --- Queries ---
	UFUNCTION(BlueprintPure) int32 GetCurrentAmmo() const { return CurrentAmmo; }
	UFUNCTION(BlueprintPure) int32 GetReserveAmmo() const { return ReserveAmmo; }
	UFUNCTION(BlueprintPure) int32 GetMagazineSize() const { return WeaponStats.MagazineSize; }
	UFUNCTION(BlueprintPure) EFireMode GetCurrentFireMode() const { return CurrentFireMode; }
	UFUNCTION(BlueprintPure) bool IsReloading() const { return bIsReloading; }
	UFUNCTION(BlueprintPure) bool IsFiring() const { return bIsFiring; }
	UFUNCTION(BlueprintPure) bool IsADS() const { return bIsADS; }
	UFUNCTION(BlueprintPure) const FWeaponStats& GetWeaponStats() const { return WeaponStats; }
	UFUNCTION(BlueprintPure) EWeaponCategory GetCategory() const { return WeaponStats.Category; }

	UPROPERTY(BlueprintAssignable) FOnWeaponFired OnWeaponFired;
	UPROPERTY(BlueprintAssignable) FOnReloadComplete OnReloadComplete;
	UPROPERTY(BlueprintAssignable) FOnAmmoChanged OnAmmoChanged;

protected:
	UPROPERTY(VisibleAnywhere) TObjectPtr<USkeletalMeshComponent> WeaponMesh;
	UPROPERTY(VisibleAnywhere) TObjectPtr<UWeaponRecoilComponent> RecoilComp;
	UPROPERTY(VisibleAnywhere) TObjectPtr<UWeaponSwayComponent> SwayComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon") FWeaponStats WeaponStats;
	UPROPERTY(EditAnywhere, Category="Weapon") FRecoilPattern RecoilPattern;

	UPROPERTY(Replicated) int32 CurrentAmmo = 30;
	UPROPERTY(Replicated) int32 ReserveAmmo = 120;
	UPROPERTY(Replicated) EFireMode CurrentFireMode = EFireMode::Auto;
	UPROPERTY(Replicated) bool bIsFiring = false;
	UPROPERTY(Replicated) bool bIsReloading = false;
	bool bIsADS = false;

	float LastFireTime = 0.0f;
	int32 BurstShotsFired = 0;
	FTimerHandle ReloadTimer;
	FTimerHandle FireTimer;

	virtual void FireShot();
	virtual void ProcessHit(const FHitResult& Hit);
	void FinishReload();
	bool CanFire() const;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
