// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"
UCLASS(Abstract, Blueprintable) class DROPER_API UMainMenuWidget : public UUserWidget { GENERATED_BODY() public:
	UFUNCTION(BlueprintCallable) void OnPlayClicked();
	UFUNCTION(BlueprintCallable) void OnSettingsClicked();
	UFUNCTION(BlueprintCallable) void OnQuitClicked();
	UFUNCTION(BlueprintCallable) void OnStashClicked();
	UFUNCTION(BlueprintCallable) void OnLoadoutClicked();
protected: virtual void NativeConstruct() override; };
