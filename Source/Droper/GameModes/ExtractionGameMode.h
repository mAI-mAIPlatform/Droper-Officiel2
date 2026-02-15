// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "DroperGameModeBase.h"
#include "ExtractionGameMode.generated.h"

UCLASS()
class DROPER_API AExtractionGameMode : public ADroperGameModeBase
{
	GENERATED_BODY()
public:
	AExtractionGameMode();
	virtual void StartMatch_Droper() override;
	virtual void EndMatch() override;
	UFUNCTION(BlueprintCallable) void OnPlayerExtracted(AController* Player);
	UFUNCTION(BlueprintCallable) void ActivateExtractionPoints();
protected:
	UPROPERTY(EditAnywhere) int32 MinExtractPlayers = 1;
	UPROPERTY(EditAnywhere) float RaidDuration = 2700.0f; // 45 min
	UPROPERTY(EditAnywhere) float ExtractionActivationTime = 600.0f;
	FTimerHandle ExtractionActivationTimer;
};
