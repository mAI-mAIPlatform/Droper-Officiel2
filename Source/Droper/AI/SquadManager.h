// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SquadManager.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPER_API USquadManager : public UActorComponent
{
	GENERATED_BODY()
public:
	USquadManager();
	UFUNCTION(BlueprintCallable) void AddMember(AActor* Member);
	UFUNCTION(BlueprintCallable) void RemoveMember(AActor* Member);
	UFUNCTION(BlueprintCallable) void IssueOrder(FName OrderType, FVector TargetLocation);
	UFUNCTION(BlueprintPure) int32 GetSquadSize() const { return Members.Num(); }
	UFUNCTION(BlueprintPure) AActor* GetLeader() const { return Members.Num() > 0 ? Members[0].Get() : nullptr; }
protected:
	TArray<TWeakObjectPtr<AActor>> Members;
	UPROPERTY(EditAnywhere) int32 MaxSquadSize = 4;
};
