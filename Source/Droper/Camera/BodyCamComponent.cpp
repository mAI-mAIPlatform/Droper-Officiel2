// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "BodyCamComponent.h"
#include "Camera/CameraComponent.h"
UBodyCamComponent::UBodyCamComponent() { PrimaryComponentTick.bCanEverTick = true; }
void UBodyCamComponent::TickComponent(float DT, ELevelTick T, FActorComponentTickFunction* F) { Super::TickComponent(DT, T, F); }
void UBodyCamComponent::SetBodyCamEnabled(bool bE) { bBodyCamActive = bE; }
