// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ProgressionSubsystem.generated.h"

UCLASS()
class DROPER_API UProgressionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& C) override;
	UFUNCTION(BlueprintCallable) void AddXP(int32 Amount);
	UFUNCTION(BlueprintCallable) void UnlockItem(FName ItemId);
	UFUNCTION(BlueprintPure) int32 GetLevel() const { return Level; }
	UFUNCTION(BlueprintPure) int32 GetXP() const { return CurrentXP; }
	UFUNCTION(BlueprintPure) int32 GetXPForNextLevel() const;
	UFUNCTION(BlueprintPure) bool IsItemUnlocked(FName ItemId) const;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUp, int32, NewLevel);
	UPROPERTY(BlueprintAssignable) FOnLevelUp OnLevelUp;
protected:
	int32 Level = 1, CurrentXP = 0;
	TSet<FName> UnlockedItems;
};
