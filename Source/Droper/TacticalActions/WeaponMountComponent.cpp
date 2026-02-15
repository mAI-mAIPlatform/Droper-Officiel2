// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "WeaponMountComponent.h"
UWeaponMountComponent::UWeaponMountComponent() { PrimaryComponentTick.bCanEverTick = false; }
bool UWeaponMountComponent::TryMount()
{
	ACharacter* Owner = Cast<ACharacter>(GetOwner());
	if (!Owner) return false;
	FVector Start; FRotator Rot; Cast<APlayerController>(Owner->GetController())->GetPlayerViewPoint(Start, Rot);
	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, Start + Rot.Vector() * MountTraceDistance, ECC_Visibility))
	{ bIsMounted = true; return true; }
	return false;
}
void UWeaponMountComponent::Unmount() { bIsMounted = false; }
