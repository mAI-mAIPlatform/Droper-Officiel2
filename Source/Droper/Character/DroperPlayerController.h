// Copyright (c) 2026 mCompany. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DroperPlayerController.generated.h"

class UInputMappingContext;
class ADroperCharacter;
class UInteractionComponent;

UCLASS()
class DROPER_API ADroperPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADroperPlayerController();

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Droper|Controller")
	void TogglePauseMenu();

	UFUNCTION(BlueprintCallable, Category = "Droper|Controller")
	void TransitionToSpectator();

	UFUNCTION(BlueprintCallable, Category = "Droper|Controller")
	void ShowDeathScreen(AController* Killer);

	UFUNCTION(BlueprintPure, Category = "Droper|Controller")
	ADroperCharacter* GetDroperCharacter() const;

	// --- Interaction Trace ---
	UFUNCTION(BlueprintPure, Category = "Droper|Controller")
	AActor* GetCurrentInteractionTarget() const { return CurrentInteractionTarget; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Droper|Input")
	TObjectPtr<UInputMappingContext> MenuMappingContext;

	UPROPERTY()
	TObjectPtr<AActor> CurrentInteractionTarget;

	UPROPERTY(EditDefaultsOnly, Category = "Droper|Controller")
	float InteractionTraceDistance = 300.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Droper|Controller")
	float InteractionTraceRadius = 20.0f;

	void PerformInteractionTrace();

	UPROPERTY()
	bool bIsPaused = false;
};
