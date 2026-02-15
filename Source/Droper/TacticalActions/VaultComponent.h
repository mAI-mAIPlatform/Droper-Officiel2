// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VaultComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPER_API UVaultComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UVaultComponent();
	UFUNCTION(BlueprintCallable) bool TryVault();
	UFUNCTION(BlueprintPure) bool IsVaulting() const { return bIsVaulting; }
	UFUNCTION(BlueprintPure) float GetVaultProgress() const;
	virtual void TickComponent(float DT, ELevelTick T, FActorComponentTickFunction* F) override;
protected:
	bool bIsVaulting = false;
	float VaultTimer = 0.0f;
	FVector VaultStart, VaultEnd;
	UPROPERTY(EditAnywhere) float VaultTraceDistance = 100.0f;
	UPROPERTY(EditAnywhere) float MaxVaultHeight = 150.0f;
	UPROPERTY(EditAnywhere) float VaultDuration = 0.6f;
	bool DetectVaultSurface(FVector& OutStart, FVector& OutEnd);
};
