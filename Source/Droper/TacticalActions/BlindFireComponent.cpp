// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "BlindFireComponent.h"
UBlindFireComponent::UBlindFireComponent() { PrimaryComponentTick.bCanEverTick = false; }
void UBlindFireComponent::StartBlindFire(bool bOver) { bBlindFiring = true; bOverCover = bOver; }
void UBlindFireComponent::StopBlindFire() { bBlindFiring = false; }
FVector UBlindFireComponent::GetBlindFireOffset() const { return bOverCover ? OverCoverOffset : SideCoverOffset; }
