// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MapDataAsset.generated.h"

UCLASS(BlueprintType)
class DROPER_API UMapDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FName MapId;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FText DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TSoftObjectPtr<UWorld> MapLevel;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TSoftObjectPtr<UTexture2D> LoadingScreen;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TSoftObjectPtr<UTexture2D> MinimapTexture;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 MinPlayers = 2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 MaxPlayers = 16;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FName> SupportedGameModes;
	virtual FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId("Map", MapId); }
};
