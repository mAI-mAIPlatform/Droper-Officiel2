// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "Types/AITypes.h"
#include "DroperAIController.generated.h"

UCLASS()
class DROPER_API ADroperAIController : public AAIController
{
	GENERATED_BODY()
public:
	ADroperAIController();
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable) void SetCombatTarget(AActor* Target);
	UFUNCTION(BlueprintCallable) void SetPatrolPath(const TArray<FVector>& Points);
	UFUNCTION(BlueprintPure) AActor* GetCombatTarget() const { return CombatTarget.Get(); }
	UFUNCTION(BlueprintPure) EThreatLevel GetThreatLevel() const { return CurrentThreat; }
protected:
	UPROPERTY(EditAnywhere) TObjectPtr<UBehaviorTree> DefaultBehaviorTree;
	UPROPERTY(EditAnywhere) TObjectPtr<class UAIPerceptionComponent> PerceptionComp;
	TWeakObjectPtr<AActor> CombatTarget;
	EThreatLevel CurrentThreat = EThreatLevel::None;
	TArray<FVector> PatrolPoints;
	UFUNCTION() void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);
};
