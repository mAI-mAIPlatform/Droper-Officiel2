// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Weapons/WeaponRecoilComponent.h"
#include "Weapons/WeaponSwayComponent.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);
	RecoilComp = CreateDefaultSubobject<UWeaponRecoilComponent>(TEXT("Recoil"));
	SwayComp = CreateDefaultSubobject<UWeaponSwayComponent>(TEXT("Sway"));
}

void AWeaponBase::BeginPlay() { Super::BeginPlay(); CurrentAmmo = WeaponStats.MagazineSize; }
void AWeaponBase::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void AWeaponBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& Out) const
{
	Super::GetLifetimeReplicatedProps(Out);
	DOREPLIFETIME(AWeaponBase, CurrentAmmo);
	DOREPLIFETIME(AWeaponBase, ReserveAmmo);
	DOREPLIFETIME(AWeaponBase, CurrentFireMode);
	DOREPLIFETIME(AWeaponBase, bIsFiring);
	DOREPLIFETIME(AWeaponBase, bIsReloading);
}

bool AWeaponBase::CanFire() const { return CurrentAmmo > 0 && !bIsReloading; }

void AWeaponBase::StartFire()
{
	if (!CanFire()) return;
	bIsFiring = true;
	BurstShotsFired = 0;
	FireShot();
	if (CurrentFireMode == EFireMode::Auto)
	{
		float Interval = 60.0f / WeaponStats.FireRate;
		GetWorldTimerManager().SetTimer(FireTimer, this, &AWeaponBase::FireShot, Interval, true);
	}
}

void AWeaponBase::StopFire()
{
	bIsFiring = false;
	GetWorldTimerManager().ClearTimer(FireTimer);
	if (RecoilComp) RecoilComp->ResetRecoil();
}

void AWeaponBase::FireShot()
{
	if (!CanFire()) { StopFire(); return; }

	CurrentAmmo--;
	OnAmmoChanged.Broadcast(CurrentAmmo);
	OnWeaponFired.Broadcast();

	if (RecoilComp) RecoilComp->ApplyRecoil(RecoilPattern, BurstShotsFired);

	// Trace
	AController* OwnerController = GetInstigatorController();
	if (OwnerController)
	{
		FVector Start; FRotator Rot;
		OwnerController->GetPlayerViewPoint(Start, Rot);
		FVector End = Start + Rot.Vector() * WeaponStats.EffectiveRange;

		FHitResult Hit;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(GetOwner());

		if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_GameTraceChannel1, Params))
		{
			ProcessHit(Hit);
		}
	}

	BurstShotsFired++;
	if (CurrentFireMode == EFireMode::Semi) StopFire();
	else if (CurrentFireMode == EFireMode::Burst && BurstShotsFired >= 3) StopFire();
	if (CurrentAmmo <= 0) StopFire();
}

void AWeaponBase::ProcessHit(const FHitResult& Hit) { /* Damage applied by ballistics subsystem */ }

void AWeaponBase::Reload()
{
	if (bIsReloading || CurrentAmmo >= WeaponStats.MagazineSize || ReserveAmmo <= 0) return;
	bIsReloading = true;
	GetWorldTimerManager().SetTimer(ReloadTimer, this, &AWeaponBase::FinishReload, WeaponStats.ReloadTime);
}

void AWeaponBase::FinishReload()
{
	int32 Needed = WeaponStats.MagazineSize - CurrentAmmo;
	int32 ToReload = FMath::Min(Needed, ReserveAmmo);
	CurrentAmmo += ToReload;
	ReserveAmmo -= ToReload;
	bIsReloading = false;
	OnAmmoChanged.Broadcast(CurrentAmmo);
	OnReloadComplete.Broadcast();
}

void AWeaponBase::CancelReload() { bIsReloading = false; GetWorldTimerManager().ClearTimer(ReloadTimer); }

void AWeaponBase::SwitchFireMode()
{
	const TArray<EFireMode>& Modes = WeaponStats.AvailableFireModes;
	if (Modes.Num() <= 1) return;
	int32 Idx = Modes.Find(CurrentFireMode);
	CurrentFireMode = Modes[(Idx + 1) % Modes.Num()];
}

void AWeaponBase::SetADS(bool bAiming) { bIsADS = bAiming; }
