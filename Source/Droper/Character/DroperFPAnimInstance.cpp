// Copyright (c) 2026 mCompany. All Rights Reserved.

#include "DroperFPAnimInstance.h"
#include "Character/DroperCharacter.h"

void UDroperFPAnimInstance::NativeInitializeAnimation() { Super::NativeInitializeAnimation(); OwnerCharacter = Cast<ADroperCharacter>(TryGetPawnOwner()); }
void UDroperFPAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (!OwnerCharacter.IsValid()) return;
	bIsADS = OwnerCharacter->IsADS();
	SprintBlend = OwnerCharacter->IsSprinting() ? 1.0f : 0.0f;
	// Sway from mouse delta — driven by heartbeat component in full impl
	FVector2D MouseDelta;
	APlayerController* PC = Cast<APlayerController>(OwnerCharacter->GetController());
	if (PC) { PC->GetInputMouseDelta(SwayX, SwayY); }
}
