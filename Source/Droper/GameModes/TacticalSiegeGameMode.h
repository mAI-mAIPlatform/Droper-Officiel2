// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "DroperGameModeBase.h"
#include "TacticalSiegeGameMode.generated.h"
UCLASS() class DROPER_API ATacticalSiegeGameMode : public ADroperGameModeBase { GENERATED_BODY() public: ATacticalSiegeGameMode();
	virtual void StartMatch_Droper() override;
	UFUNCTION(BlueprintCallable) void OnBombPlanted(); UFUNCTION(BlueprintCallable) void OnBombDefused();
protected: UPROPERTY(EditAnywhere) float BombTimer = 45.0f; UPROPERTY(EditAnywhere) int32 RoundsToWin = 4; int32 AttackerWins = 0, DefenderWins = 0; };
