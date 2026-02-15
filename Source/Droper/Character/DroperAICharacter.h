// Copyright (c) 2026 mCompany. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/DroperCharacterBase.h"
#include "Types/AITypes.h"
#include "DroperAICharacter.generated.h"

class UAIPerceptionStimuliSourceComponent;

UCLASS()
class DROPER_API ADroperAICharacter : public ADroperCharacterBase
{
	GENERATED_BODY()

public:
	ADroperAICharacter();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure, Category = "Droper|AI")
	EAIState GetAIState() const { return CurrentAIState; }

	UFUNCTION(BlueprintCallable, Category = "Droper|AI")
	void SetAIState(EAIState NewState);

	UFUNCTION(BlueprintPure, Category = "Droper|AI")
	EBehaviorProfile GetBehaviorProfile() const { return BehaviorProfile; }

	UFUNCTION(BlueprintPure, Category = "Droper|AI")
	ESquadRole GetSquadRole() const { return SquadRole; }

	UFUNCTION(BlueprintCallable, Category = "Droper|AI")
	void SetAlertLevel(EThreatLevel NewLevel);

	UFUNCTION(BlueprintPure, Category = "Droper|AI")
	EThreatLevel GetAlertLevel() const { return AlertLevel; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Droper|AI")
	TObjectPtr<UAIPerceptionStimuliSourceComponent> PerceptionStimuli;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Droper|AI")
	EBehaviorProfile BehaviorProfile = EBehaviorProfile::Tactical;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Droper|AI")
	ESquadRole SquadRole = ESquadRole::Rifleman;

	UPROPERTY(BlueprintReadOnly, Category = "Droper|AI")
	EAIState CurrentAIState = EAIState::Idle;

	UPROPERTY(BlueprintReadOnly, Category = "Droper|AI")
	EThreatLevel AlertLevel = EThreatLevel::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Droper|AI")
	FAIAccuracyProfile AccuracyProfile;
};
