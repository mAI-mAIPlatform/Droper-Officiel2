// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HemorrhageEffect.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPER_API UHemorrhageEffect : public UActorComponent
{
	GENERATED_BODY()
public:
	UHemorrhageEffect();
	virtual void TickComponent(float DT, ELevelTick T, FActorComponentTickFunction* F) override;
	UFUNCTION(BlueprintCallable) void StartBleeding(float Rate);
	UFUNCTION(BlueprintCallable) void ApplyBandage();
	UFUNCTION(BlueprintPure) bool IsBleeding() const { return bBleeding; }
	UFUNCTION(BlueprintPure) float GetBleedRate() const { return BleedRate; }
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBleedTick, float, DamageThisTick);
	UPROPERTY(BlueprintAssignable) FOnBleedTick OnBleedTick;
protected:
	bool bBleeding = false;
	float BleedRate = 0.0f;
	float BandageProgress = 0.0f;
	UPROPERTY(EditAnywhere) float BandageTime = 4.0f;
};
