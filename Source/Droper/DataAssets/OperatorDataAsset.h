// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "OperatorDataAsset.generated.h"

UCLASS(BlueprintType)
class DROPER_API UOperatorDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FName OperatorId;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FText DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FText Bio;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TSoftObjectPtr<USkeletalMesh> CharacterMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TSoftObjectPtr<UTexture2D> Portrait;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float BaseHealth = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float BaseSpeed = 450.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FName UniqueAbility;
	virtual FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId("Operator", OperatorId); }
};
