// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "CharacterVoiceComponent.h"
#include "Kismet/GameplayStatics.h"

UCharacterVoiceComponent::UCharacterVoiceComponent() { PrimaryComponentTick.bCanEverTick = false; }

void UCharacterVoiceComponent::PlayBark(EVoiceBark BarkType)
{
	float CurrentTime = GetWorld()->GetTimeSeconds();
	if (CurrentTime - LastBarkTime < BarkCooldown) return;
	if (VoicePack) { UGameplayStatics::PlaySoundAtLocation(this, VoicePack, GetOwner()->GetActorLocation()); }
	LastBarkTime = CurrentTime;
}
