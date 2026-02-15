// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StaminaComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPER_API UStaminaComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UStaminaComponent();
	virtual void TickComponent(float DT, ELevelTick T, FActorComponentTickFunction* F) override;
	UFUNCTION(BlueprintCallable) void DrainStamina(float Amount);
	UFUNCTION(BlueprintCallable) void SetDrainMultiplier(float Mult) { DrainMultiplier = Mult; }
	UFUNCTION(BlueprintPure) float GetCurrentStamina() const { return CurrentStamina; }
	UFUNCTION(BlueprintPure) float GetStaminaPercent() const { return MaxStamina > 0 ? CurrentStamina / MaxStamina : 0; }
	UFUNCTION(BlueprintPure) bool IsExhausted() const { return CurrentStamina <= 0.0f; }
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStaminaDepleted);
	UPROPERTY(BlueprintAssignable) FOnStaminaDepleted OnStaminaDepleted;
protected:
	UPROPERTY(EditAnywhere) float MaxStamina = 100.0f;
	UPROPERTY(EditAnywhere) float CurrentStamina = 100.0f;
	UPROPERTY(EditAnywhere) float RegenRate = 8.0f;
	UPROPERTY(EditAnywhere) float RegenDelay = 2.0f;
	float DrainMultiplier = 1.0f;
	float TimeSinceLastDrain = 0.0f;
};
