// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "AttachmentManagerComponent.h"
UAttachmentManagerComponent::UAttachmentManagerComponent() { PrimaryComponentTick.bCanEverTick = false; }
bool UAttachmentManagerComponent::AttachToSlot(EAttachmentSlot Slot, const FAttachmentModifiers& Mods)
{
	if (Attachments.Contains(Slot)) return false;
	Attachments.Add(Slot, Mods);
	return true;
}
bool UAttachmentManagerComponent::DetachFromSlot(EAttachmentSlot Slot) { return Attachments.Remove(Slot) > 0; }
bool UAttachmentManagerComponent::HasAttachment(EAttachmentSlot Slot) const { return Attachments.Contains(Slot); }
FAttachmentModifiers UAttachmentManagerComponent::GetCombinedModifiers() const
{
	FAttachmentModifiers Combined;
	for (const auto& Pair : Attachments)
	{
		Combined.RecoilMultiplier *= Pair.Value.RecoilMultiplier;
		Combined.SpreadMultiplier *= Pair.Value.SpreadMultiplier;
		Combined.ADSSpeedMultiplier *= Pair.Value.ADSSpeedMultiplier;
		Combined.RangeMultiplier *= Pair.Value.RangeMultiplier;
		Combined.WeightModifier += Pair.Value.WeightModifier;
		Combined.NoiseMultiplier *= Pair.Value.NoiseMultiplier;
	}
	return Combined;
}
