// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "InputModifiers.h"
#include "HeartRateInputModifier.generated.h"

UCLASS()
class DROPER_API UHeartRateInputModifier : public UInputModifier
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere) float MaxSwayMultiplier = 2.0f;
protected:
	virtual FInputActionValue ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime) override;
};
