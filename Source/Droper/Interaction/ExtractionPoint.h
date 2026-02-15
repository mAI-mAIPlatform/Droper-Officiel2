// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/InteractableInterface.h"
#include "ExtractionPoint.generated.h"

UCLASS(Blueprintable)
class DROPER_API AExtractionPoint : public AActor, public IInteractable
{
	GENERATED_BODY()
public:
	AExtractionPoint();
	virtual void OnInteract_Implementation(AActor* Instigator) override;
	virtual FText GetInteractionText_Implementation() const override;
	virtual bool CanInteract_Implementation(AActor* Instigator) const override;
	virtual void OnStartFocus_Implementation(AActor* I) override {}
	virtual void OnEndFocus_Implementation(AActor* I) override {}
	UFUNCTION(BlueprintPure) bool IsActive() const { return bIsActive; }
	UFUNCTION(BlueprintCallable) void ActivateExtraction();
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExtractionStarted, AActor*, Player);
	UPROPERTY(BlueprintAssignable) FOnExtractionStarted OnExtractionStarted;
protected:
	UPROPERTY(EditAnywhere) float ExtractionTime = 10.0f;
	UPROPERTY(EditAnywhere) int32 MaxPlayers = 4;
	bool bIsActive = false;
	UPROPERTY(VisibleAnywhere) TObjectPtr<class UBoxComponent> TriggerVolume;
};
