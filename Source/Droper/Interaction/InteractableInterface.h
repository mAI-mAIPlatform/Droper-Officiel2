// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable) class UInteractable : public UInterface { GENERATED_BODY() };
class DROPER_API IInteractable
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction") void OnInteract(AActor* Instigator);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction") void OnStartFocus(AActor* Instigator);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction") void OnEndFocus(AActor* Instigator);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction") FText GetInteractionText() const;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction") bool CanInteract(AActor* Instigator) const;
};
