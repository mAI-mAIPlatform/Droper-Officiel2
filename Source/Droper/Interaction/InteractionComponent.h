// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPER_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UInteractionComponent();
	virtual void TickComponent(float DT, ELevelTick T, FActorComponentTickFunction* F) override;
	UFUNCTION(BlueprintCallable) void PerformInteraction();
	UFUNCTION(BlueprintPure) AActor* GetFocusedInteractable() const { return FocusedActor.Get(); }
protected:
	void TraceForInteractable();
	TWeakObjectPtr<AActor> FocusedActor;
	UPROPERTY(EditAnywhere) float InteractionRange = 250.0f;
};
