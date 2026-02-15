// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterIKComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPER_API UCharacterIKComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UCharacterIKComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadOnly) FVector LeftFootOffset = FVector::ZeroVector;
	UPROPERTY(BlueprintReadOnly) FVector RightFootOffset = FVector::ZeroVector;
	UPROPERTY(BlueprintReadOnly) FVector LeftHandGripLocation = FVector::ZeroVector;
	UPROPERTY(BlueprintReadOnly) FRotator LeftHandGripRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, Category="IK") float FootTraceDistance = 50.0f;
	UPROPERTY(EditAnywhere, Category="IK") float FootInterpSpeed = 15.0f;
protected:
	void UpdateFootIK(float DeltaTime);
	void UpdateHandIK();
	FVector TraceFootPosition(FName SocketName) const;
};
