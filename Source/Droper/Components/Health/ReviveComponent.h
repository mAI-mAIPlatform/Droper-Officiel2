// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ReviveComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPER_API UReviveComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UReviveComponent();
	virtual void TickComponent(float DT, ELevelTick T, FActorComponentTickFunction* F) override;
	UFUNCTION(BlueprintCallable) void EnterDownedState();
	UFUNCTION(BlueprintCallable) void StartRevive(AActor* Reviver);
	UFUNCTION(BlueprintCallable) void CancelRevive();
	UFUNCTION(BlueprintPure) bool IsDowned() const { return bIsDowned; }
	UFUNCTION(BlueprintPure) float GetDownedTimeRemaining() const;
	UFUNCTION(BlueprintPure) float GetReviveProgress() const;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRevived);
	UPROPERTY(BlueprintAssignable) FOnRevived OnRevived;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBledOut);
	UPROPERTY(BlueprintAssignable) FOnBledOut OnBledOut;
protected:
	bool bIsDowned = false, bIsBeingRevived = false;
	float DownedTimer = 0.0f, ReviveProgress = 0.0f;
	UPROPERTY(EditAnywhere) float MaxDownedTime = 60.0f;
	UPROPERTY(EditAnywhere) float ReviveDuration = 5.0f;
	TWeakObjectPtr<AActor> CurrentReviver;
};
