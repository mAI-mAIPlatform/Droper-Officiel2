// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "WeaponRecoilComponent.h"
UWeaponRecoilComponent::UWeaponRecoilComponent() { PrimaryComponentTick.bCanEverTick = true; }
void UWeaponRecoilComponent::TickComponent(float DT, ELevelTick T, FActorComponentTickFunction* F)
{
	Super::TickComponent(DT, T, F);
	CurrentRecoil = FMath::Vector2DInterpTo(CurrentRecoil, TargetRecoil, DT, RecoilInterpSpeed);
	TargetRecoil = FMath::Vector2DInterpTo(TargetRecoil, FVector2D::ZeroVector, DT, RecoilRecoverySpeed);
}
void UWeaponRecoilComponent::ApplyRecoil(const FRecoilPattern& Pattern, int32 ShotIndex)
{
	float VerticalKick = Pattern.VerticalRecoil + FMath::FRandRange(-Pattern.RecoilRandomness, Pattern.RecoilRandomness);
	float HorizontalKick = FMath::FRandRange(-Pattern.HorizontalRecoil, Pattern.HorizontalRecoil);
	TargetRecoil += FVector2D(HorizontalKick, VerticalKick);
}
void UWeaponRecoilComponent::ResetRecoil() { TargetRecoil = FVector2D::ZeroVector; }
