// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "DroperInputConfig.generated.h"

UCLASS(BlueprintType)
class DROPER_API UDroperInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UInputMappingContext> DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UInputMappingContext> VehicleMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UInputMappingContext> MenuMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UInputAction> IA_Move;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UInputAction> IA_Look;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UInputAction> IA_Fire;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UInputAction> IA_ADS;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UInputAction> IA_Reload;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UInputAction> IA_Sprint;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UInputAction> IA_Crouch;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UInputAction> IA_Prone;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UInputAction> IA_Jump;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UInputAction> IA_LeanLeft;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UInputAction> IA_LeanRight;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UInputAction> IA_Interact;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UInputAction> IA_Vault;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UInputAction> IA_Inventory;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UInputAction> IA_Scroll;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UInputAction> IA_SwitchWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UInputAction> IA_SwitchFireMode;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UInputAction> IA_Gadget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UInputAction> IA_Ping;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UInputAction> IA_VoiceChat;
};
