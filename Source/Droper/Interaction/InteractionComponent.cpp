// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "InteractionComponent.h"
#include "Interaction/InteractableInterface.h"
UInteractionComponent::UInteractionComponent() { PrimaryComponentTick.bCanEverTick = true; }
void UInteractionComponent::TickComponent(float DT, ELevelTick T, FActorComponentTickFunction* F) { Super::TickComponent(DT, T, F); TraceForInteractable(); }
void UInteractionComponent::TraceForInteractable()
{
	APlayerController* PC = Cast<APlayerController>(Cast<APawn>(GetOwner())->GetController());
	if (!PC) return;
	FVector Start; FRotator Rot; PC->GetPlayerViewPoint(Start, Rot);
	FHitResult Hit; FCollisionQueryParams P; P.AddIgnoredActor(GetOwner());
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, Start + Rot.Vector() * InteractionRange, ECC_Visibility, P))
	{
		if (Hit.GetActor() && Hit.GetActor()->Implements<UInteractable>())
		{
			if (FocusedActor.Get() != Hit.GetActor()) { if (FocusedActor.IsValid()) IInteractable::Execute_OnEndFocus(FocusedActor.Get(), GetOwner()); FocusedActor = Hit.GetActor(); IInteractable::Execute_OnStartFocus(FocusedActor.Get(), GetOwner()); }
			return;
		}
	}
	if (FocusedActor.IsValid()) { IInteractable::Execute_OnEndFocus(FocusedActor.Get(), GetOwner()); FocusedActor = nullptr; }
}
void UInteractionComponent::PerformInteraction() { if (FocusedActor.IsValid() && IInteractable::Execute_CanInteract(FocusedActor.Get(), GetOwner())) IInteractable::Execute_OnInteract(FocusedActor.Get(), GetOwner()); }
