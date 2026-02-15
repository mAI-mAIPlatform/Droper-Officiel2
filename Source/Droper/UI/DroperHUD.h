// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DroperHUD.generated.h"

UCLASS(Abstract, Blueprintable)
class DROPER_API UDroperHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable) void UpdateHealth(float Percent);
	UFUNCTION(BlueprintCallable) void UpdateAmmo(int32 Current, int32 Reserve);
	UFUNCTION(BlueprintCallable) void UpdateStamina(float Percent);
	UFUNCTION(BlueprintCallable) void ShowHitMarker(bool bKill);
	UFUNCTION(BlueprintCallable) void ShowDamageIndicator(FVector Direction);
	UFUNCTION(BlueprintCallable) void UpdateMinimap(FVector PlayerLocation, float PlayerYaw);
	UFUNCTION(BlueprintCallable) void AddKillFeedEntry(const FString& Killer, const FString& Victim, const FString& Weapon);
	UFUNCTION(BlueprintCallable) void ShowInteractionPrompt(const FText& Text);
	UFUNCTION(BlueprintCallable) void HideInteractionPrompt();
	UFUNCTION(BlueprintCallable) void UpdateCrosshair(float Spread, bool bADS);
	UFUNCTION(BlueprintCallable) void ShowExtractionTimer(float Remaining);
protected:
	virtual void NativeConstruct() override;
};
