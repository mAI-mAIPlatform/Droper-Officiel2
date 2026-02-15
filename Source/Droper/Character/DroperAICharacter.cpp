// Copyright (c) 2026 mCompany. All Rights Reserved.

#include "DroperAICharacter.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Damage.h"

ADroperAICharacter::ADroperAICharacter()
{
	PerceptionStimuli = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("PerceptionStimuli"));
	PerceptionStimuli->RegisterForSense(UAISense_Sight::StaticClass());
	PerceptionStimuli->RegisterForSense(UAISense_Hearing::StaticClass());
	PerceptionStimuli->RegisterForSense(UAISense_Damage::StaticClass());
	PerceptionStimuli->bAutoRegister = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ADroperAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ADroperAICharacter::SetAIState(EAIState NewState)
{
	CurrentAIState = NewState;
}

void ADroperAICharacter::SetAlertLevel(EThreatLevel NewLevel)
{
	AlertLevel = NewLevel;
}
