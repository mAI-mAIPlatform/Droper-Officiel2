// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/WeaponTypes.h"
#include "AttachmentManagerComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPER_API UAttachmentManagerComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UAttachmentManagerComponent();
	UFUNCTION(BlueprintCallable) bool AttachToSlot(EAttachmentSlot Slot, const FAttachmentModifiers& Mods);
	UFUNCTION(BlueprintCallable) bool DetachFromSlot(EAttachmentSlot Slot);
	UFUNCTION(BlueprintPure) bool HasAttachment(EAttachmentSlot Slot) const;
	UFUNCTION(BlueprintPure) FAttachmentModifiers GetCombinedModifiers() const;
	UFUNCTION(BlueprintPure) int32 GetAttachmentCount() const { return Attachments.Num(); }
protected:
	UPROPERTY() TMap<EAttachmentSlot, FAttachmentModifiers> Attachments;
};
