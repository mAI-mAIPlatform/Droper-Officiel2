// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "MainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
void UMainMenuWidget::NativeConstruct() { Super::NativeConstruct(); }
void UMainMenuWidget::OnPlayClicked() {}
void UMainMenuWidget::OnSettingsClicked() {}
void UMainMenuWidget::OnQuitClicked() { UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true); }
void UMainMenuWidget::OnStashClicked() {}
void UMainMenuWidget::OnLoadoutClicked() {}
