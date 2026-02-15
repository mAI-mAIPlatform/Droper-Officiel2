// Copyright (c) 2026 mCompany. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "DroperSpectatorPawn.generated.h"

/**
 * ADroperSpectatorPawn
 * 
 * Free-cam and follow-cam spectating pawn with smooth transitions.
 */
UENUM(BlueprintType)
enum class ESpectatorMode : uint8
{
	FreeCam,
	FollowPlayer,
	FixedCamera
};

UCLASS()
class DROPER_API ADroperSpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()

public:
	ADroperSpectatorPawn();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Droper|Spectator")
	void SetSpectatorMode(ESpectatorMode NewMode);

	UFUNCTION(BlueprintCallable, Category = "Droper|Spectator")
	void FollowNextPlayer();

	UFUNCTION(BlueprintCallable, Category = "Droper|Spectator")
	void FollowPreviousPlayer();

	UFUNCTION(BlueprintPure, Category = "Droper|Spectator")
	ESpectatorMode GetSpectatorMode() const { return CurrentMode; }

	UFUNCTION(BlueprintPure, Category = "Droper|Spectator")
	AActor* GetFollowTarget() const { return FollowTarget; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Spectator")
	float FreeCamSpeed = 600.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Spectator")
	float FollowCamInterpSpeed = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Spectator")
	FVector FollowCamOffset = FVector(-200.0f, 0.0f, 100.0f);

	UPROPERTY(BlueprintReadOnly, Category = "Droper|Spectator")
	ESpectatorMode CurrentMode = ESpectatorMode::FreeCam;

	UPROPERTY()
	TObjectPtr<AActor> FollowTarget;

	UPROPERTY()
	int32 FollowTargetIndex = 0;

private:
	void UpdateFollowCamera(float DeltaTime);
	TArray<AActor*> GetSpectateTargets() const;
};
