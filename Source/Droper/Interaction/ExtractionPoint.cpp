// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "ExtractionPoint.h"
#include "Components/BoxComponent.h"
AExtractionPoint::AExtractionPoint()
{
	bReplicates = true;
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	TriggerVolume->SetBoxExtent(FVector(200)); SetRootComponent(TriggerVolume);
}
void AExtractionPoint::OnInteract_Implementation(AActor* Instigator) { if (bIsActive) OnExtractionStarted.Broadcast(Instigator); }
FText AExtractionPoint::GetInteractionText_Implementation() const { return bIsActive ? FText::FromString(TEXT("Extract")) : FText::FromString(TEXT("Extraction Locked")); }
bool AExtractionPoint::CanInteract_Implementation(AActor* Instigator) const { return bIsActive; }
void AExtractionPoint::ActivateExtraction() { bIsActive = true; }
