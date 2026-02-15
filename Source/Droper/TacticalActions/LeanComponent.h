// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LeanComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPER_API ULeanComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	ULeanComponent();
	virtual void TickComponent(float DT, ELevelTick T, FActorComponentTickFunction* F) override;
	UFUNCTION(BlueprintCallable) void SetLeanDirection(float Direction); // -1 left, 0 center, 1 right
	UFUNCTION(BlueprintPure) float GetLeanAlpha() const { return CurrentLeanAlpha; }
	UFUNCTION(BlueprintPure) FVector GetLeanOffset() const;
	UFUNCTION(BlueprintPure) float GetLeanRoll() const;
protected:
	float TargetLean = 0.0f, CurrentLeanAlpha = 0.0f;
	UPROPERTY(EditAnywhere) float LeanOffset = 40.0f;
	UPROPERTY(EditAnywhere) float LeanRollAngle = 15.0f;
	UPROPERTY(EditAnywhere) float LeanSpeed = 10.0f;
};
