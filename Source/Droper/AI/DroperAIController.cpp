// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "DroperAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"

ADroperAIController::ADroperAIController()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	auto* SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 3000.0f; SightConfig->LoseSightRadius = 3500.0f; SightConfig->PeripheralVisionAngleDegrees = 70.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true; SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	PerceptionComp->ConfigureSense(*SightConfig);
	auto* HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
	HearingConfig->HearingRange = 2000.0f;
	PerceptionComp->ConfigureSense(*HearingConfig);
	PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
}

void ADroperAIController::BeginPlay() { Super::BeginPlay(); PerceptionComp->OnPerceptionUpdated.AddDynamic(this, &ADroperAIController::OnPerceptionUpdated); }
void ADroperAIController::OnPossess(APawn* InPawn) { Super::OnPossess(InPawn); if (DefaultBehaviorTree) RunBehaviorTree(DefaultBehaviorTree); }
void ADroperAIController::Tick(float DeltaTime) { Super::Tick(DeltaTime); }
void ADroperAIController::SetCombatTarget(AActor* Target) { CombatTarget = Target; if (GetBlackboardComponent()) GetBlackboardComponent()->SetValueAsObject(FName("CombatTarget"), Target); }
void ADroperAIController::SetPatrolPath(const TArray<FVector>& Points) { PatrolPoints = Points; }
void ADroperAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors) { /* Process perceived actors, update threat */ }
