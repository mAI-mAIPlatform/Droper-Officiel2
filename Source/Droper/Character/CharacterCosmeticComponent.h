// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterCosmeticComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPER_API UCharacterCosmeticComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UCharacterCosmeticComponent();
	UFUNCTION(BlueprintCallable) void ApplySkin(TSoftObjectPtr<USkeletalMesh> SkinMesh);
	UFUNCTION(BlueprintCallable) void ApplyHelmet(TSoftObjectPtr<UStaticMesh> HelmetMesh);
	UFUNCTION(BlueprintCallable) void ApplyGloves(TSoftObjectPtr<UMaterialInterface> GloveMaterial);
protected:
	UPROPERTY(EditAnywhere, Category="Cosmetic") FName HelmetSocket = FName("helmet_socket");
	UPROPERTY() TObjectPtr<UStaticMeshComponent> HelmetMeshComp;
};
