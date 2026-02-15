// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "VaultComponent.h"
#include "GameFramework/Character.h"

UVaultComponent::UVaultComponent() { PrimaryComponentTick.bCanEverTick = true; }

bool UVaultComponent::TryVault()
{
	if (bIsVaulting) return false;
	FVector Start, End;
	if (!DetectVaultSurface(Start, End)) return false;
	VaultStart = Start; VaultEnd = End; bIsVaulting = true; VaultTimer = 0.0f;
	return true;
}

void UVaultComponent::TickComponent(float DT, ELevelTick T, FActorComponentTickFunction* F)
{
	Super::TickComponent(DT, T, F);
	if (!bIsVaulting) return;
	VaultTimer += DT;
	float Alpha = FMath::Clamp(VaultTimer / VaultDuration, 0.0f, 1.0f);
	ACharacter* Owner = Cast<ACharacter>(GetOwner());
	if (Owner) Owner->SetActorLocation(FMath::Lerp(VaultStart, VaultEnd, Alpha));
	if (Alpha >= 1.0f) bIsVaulting = false;
}

float UVaultComponent::GetVaultProgress() const { return VaultDuration > 0 ? VaultTimer / VaultDuration : 0; }

bool UVaultComponent::DetectVaultSurface(FVector& OutStart, FVector& OutEnd)
{
	ACharacter* Owner = Cast<ACharacter>(GetOwner());
	if (!Owner) return false;
	FVector Loc = Owner->GetActorLocation();
	FVector Fwd = Owner->GetActorForwardVector();
	// Forward trace to detect wall
	FHitResult WallHit;
	if (!GetWorld()->LineTraceSingleByChannel(WallHit, Loc, Loc + Fwd * VaultTraceDistance, ECC_Visibility)) return false;
	// Height trace
	FVector TopCheck = WallHit.ImpactPoint + FVector(0, 0, MaxVaultHeight);
	FHitResult TopHit;
	if (!GetWorld()->LineTraceSingleByChannel(TopHit, TopCheck, TopCheck - FVector(0, 0, MaxVaultHeight * 2), ECC_Visibility)) return false;
	if (TopHit.ImpactPoint.Z - Loc.Z > MaxVaultHeight) return false;
	OutStart = Loc;
	OutEnd = TopHit.ImpactPoint + FVector(0, 0, Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()) + Fwd * 50.0f;
	return true;
}
