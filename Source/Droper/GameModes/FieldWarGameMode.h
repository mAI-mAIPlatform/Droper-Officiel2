// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "DroperGameModeBase.h"
#include "FieldWarGameMode.generated.h"
UCLASS() class DROPER_API AFieldWarGameMode : public ADroperGameModeBase { GENERATED_BODY() public: AFieldWarGameMode();
	virtual void StartMatch_Droper() override;
	UFUNCTION(BlueprintCallable) void OnObjectiveCaptured(int32 TeamId, int32 ObjectiveIndex);
protected: UPROPERTY(EditAnywhere) int32 TotalObjectives = 5; UPROPERTY(EditAnywhere) int32 TicketsPerTeam = 300; TMap<int32, int32> TeamTickets; };
