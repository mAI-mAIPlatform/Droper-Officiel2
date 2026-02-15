// Copyright (c) 2026 mCompany. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/DroperCharacterBase.h"
#include "InputActionValue.h"
#include "DroperCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UEquipmentComponent;
class UBodyCamPostProcessComponent;
class UInteractionComponent;
class UStaminaComponent;
class ULeanComponent;
class UVaultComponent;
class UInputMappingContext;
class UInputAction;

/**
 * ADroperCharacter
 *
 * Player-controlled tactical character with body-cam, enhanced input,
 * lean/vault, stamina, equipment, and interaction systems.
 */
UCLASS()
class DROPER_API ADroperCharacter : public ADroperCharacterBase
{
	GENERATED_BODY()

public:
	ADroperCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	virtual void OnRep_PlayerState() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// --- Camera ---
	UFUNCTION(BlueprintPure, Category = "Droper|Character")
	UCameraComponent* GetFirstPersonCamera() const { return FirstPersonCamera; }

	// --- Components Getters ---
	UFUNCTION(BlueprintPure, Category = "Droper|Character")
	UEquipmentComponent* GetEquipmentComponent() const { return EquipmentComp; }

	UFUNCTION(BlueprintPure, Category = "Droper|Character")
	UStaminaComponent* GetStaminaComponent() const { return StaminaComp; }

	UFUNCTION(BlueprintPure, Category = "Droper|Character")
	UInteractionComponent* GetInteractionComponent() const { return InteractionComp; }

	UFUNCTION(BlueprintPure, Category = "Droper|Character")
	ULeanComponent* GetLeanComponent() const { return LeanComp; }

	// --- Movement State ---
	UFUNCTION(BlueprintPure, Category = "Droper|Character")
	bool IsSprinting() const { return bIsSprinting; }

	UFUNCTION(BlueprintPure, Category = "Droper|Character")
	bool IsADS() const { return bIsADS; }

	UFUNCTION(BlueprintPure, Category = "Droper|Character")
	float GetCurrentMoveSpeed() const;

protected:
	// --- Camera ---
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Droper|Camera")
	TObjectPtr<UCameraComponent> FirstPersonCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Droper|Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	// --- Components ---
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Droper|Components")
	TObjectPtr<UEquipmentComponent> EquipmentComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Droper|Components")
	TObjectPtr<UBodyCamPostProcessComponent> BodyCamComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Droper|Components")
	TObjectPtr<UInteractionComponent> InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Droper|Components")
	TObjectPtr<UStaminaComponent> StaminaComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Droper|Components")
	TObjectPtr<ULeanComponent> LeanComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Droper|Components")
	TObjectPtr<UVaultComponent> VaultComp;

	// --- Enhanced Input ---
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Input")
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Input")
	TObjectPtr<UInputAction> IA_Look;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Input")
	TObjectPtr<UInputAction> IA_Fire;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Input")
	TObjectPtr<UInputAction> IA_ADS;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Input")
	TObjectPtr<UInputAction> IA_Reload;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Input")
	TObjectPtr<UInputAction> IA_Sprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Input")
	TObjectPtr<UInputAction> IA_Crouch;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Input")
	TObjectPtr<UInputAction> IA_Prone;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Input")
	TObjectPtr<UInputAction> IA_Jump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Input")
	TObjectPtr<UInputAction> IA_LeanLeft;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Input")
	TObjectPtr<UInputAction> IA_LeanRight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Input")
	TObjectPtr<UInputAction> IA_Interact;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Input")
	TObjectPtr<UInputAction> IA_Vault;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Input")
	TObjectPtr<UInputAction> IA_Inventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Input")
	TObjectPtr<UInputAction> IA_Scroll;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Input")
	TObjectPtr<UInputAction> IA_SwitchWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Input")
	TObjectPtr<UInputAction> IA_SwitchFireMode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Input")
	TObjectPtr<UInputAction> IA_Gadget1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Input")
	TObjectPtr<UInputAction> IA_Gadget2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Input")
	TObjectPtr<UInputAction> IA_Ping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Droper|Input")
	TObjectPtr<UInputAction> IA_VoiceChat;

	// --- State ---
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Droper|Character")
	bool bIsSprinting = false;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Droper|Character")
	bool bIsADS = false;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Droper|Character")
	bool bIsProne = false;

	// --- Input Handlers ---
	void HandleMove(const FInputActionValue& Value);
	void HandleLook(const FInputActionValue& Value);
	void HandleFireStarted();
	void HandleFireCompleted();
	void HandleADSStarted();
	void HandleADSCompleted();
	void HandleReload();
	void HandleSprintStarted();
	void HandleSprintCompleted();
	void HandleCrouch();
	void HandleProne();
	void HandleJump();
	void HandleLeanLeftStarted();
	void HandleLeanLeftCompleted();
	void HandleLeanRightStarted();
	void HandleLeanRightCompleted();
	void HandleInteract();
	void HandleVault();
	void HandleInventory();
	void HandleScroll(const FInputActionValue& Value);
	void HandleSwitchWeapon(const FInputActionValue& Value);
	void HandleSwitchFireMode();
	void HandleGadget1();
	void HandleGadget2();
	void HandlePing();
	void HandleVoiceChatStarted();
	void HandleVoiceChatCompleted();

	// --- Server RPCs ---
	UFUNCTION(Server, Reliable)
	void Server_SetSprinting(bool bSprint);

	UFUNCTION(Server, Reliable)
	void Server_SetADS(bool bAiming);

	UFUNCTION(Server, Reliable)
	void Server_Fire();

	UFUNCTION(Server, Reliable)
	void Server_Reload();

private:
	void SetupInputMappingContext();
	void RemoveInputMappingContext();
};
