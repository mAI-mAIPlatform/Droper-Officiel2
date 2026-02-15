// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPER_API UHealingComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UHealingComponent();
	virtual void TickComponent(float DT, ELevelTick T, FActorComponentTickFunction* F) override;
	UFUNCTION(BlueprintCallable) void StartHealing(float HealAmount, float Duration, int32 TargetBodyPart);
	UFUNCTION(BlueprintCallable) void CancelHealing();
	UFUNCTION(BlueprintPure) bool IsHealing() const { return bIsHealing; }
	UFUNCTION(BlueprintPure) float GetHealProgress() const;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealComplete, int32, BodyPart, float, AmountHealed);
	UPROPERTY(BlueprintAssignable) FOnHealComplete OnHealComplete;
protected:
	bool bIsHealing = false;
	float HealTimer = 0.0f, HealDuration = 0.0f, HealAmount = 0.0f;
	int32 TargetPart = 0;
};
