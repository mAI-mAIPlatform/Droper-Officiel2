// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DroperSpectatorController.generated.h"

UCLASS()
class DROPER_API ADroperSpectatorController : public APlayerController
{
	GENERATED_BODY()
public:
	ADroperSpectatorController();
	virtual void SetupInputComponent() override;
	UFUNCTION(BlueprintCallable) void CycleNextTarget();
	UFUNCTION(BlueprintCallable) void CyclePreviousTarget();
	UFUNCTION(BlueprintCallable) void ToggleFreeCam();
protected:
	UPROPERTY() int32 CurrentTargetIndex = 0;
	UPROPERTY() bool bFreeCam = false;
};
