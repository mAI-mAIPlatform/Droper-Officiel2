// Copyright (c) 2026 mCompany. All Rights Reserved.

#include "DroperCharacter.h"
#include "Droper/Droper.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Components/EquipmentComponent.h"
#include "Components/BodyCamPostProcessComponent.h"
#include "Interaction/InteractionComponent.h"
#include "Components/Health/StaminaComponent.h"
#include "Actions/LeanComponent.h"
#include "Actions/VaultComponent.h"
#include "Net/UnrealNetwork.h"

ADroperCharacter::ADroperCharacter()
{
	// Camera boom (minimal arm length for body-cam feel)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh(), FName("head"));
	CameraBoom->TargetArmLength = 0.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bDoCollisionTest = false;

	// First-person camera
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(CameraBoom);
	FirstPersonCamera->bUsePawnControlRotation = false;
	FirstPersonCamera->SetFieldOfView(100.0f); // Wide FOV for body-cam

	// Components
	EquipmentComp = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EquipmentComponent"));
	BodyCamComp = CreateDefaultSubobject<UBodyCamPostProcessComponent>(TEXT("BodyCamPostProcess"));
	InteractionComp = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
	StaminaComp = CreateDefaultSubobject<UStaminaComponent>(TEXT("StaminaComponent"));
	LeanComp = CreateDefaultSubobject<ULeanComponent>(TEXT("LeanComponent"));
	VaultComp = CreateDefaultSubobject<UVaultComponent>(TEXT("VaultComponent"));

	// Movement defaults
	GetCharacterMovement()->MaxWalkSpeed = 450.0f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 200.0f;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	GetCharacterMovement()->BrakingDecelerationWalking = 1400.0f;
	GetCharacterMovement()->JumpZVelocity = 350.0f;
	GetCharacterMovement()->AirControl = 0.15f;
}

void ADroperCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetupInputMappingContext();
}

void ADroperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Sprint stamina drain
	if (bIsSprinting && StaminaComp)
	{
		float DrainRate = 10.0f;
		if (EquipmentComp)
		{
			DrainRate *= EquipmentComp->GetStaminaDrainMultiplier();
		}
		StaminaComp->DrainStamina(DrainRate * DeltaTime);

		if (StaminaComp->GetCurrentStamina() <= 0.0f)
		{
			HandleSprintCompleted();
		}
	}
}

void ADroperCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADroperCharacter, bIsSprinting);
	DOREPLIFETIME(ADroperCharacter, bIsADS);
	DOREPLIFETIME(ADroperCharacter, bIsProne);
}

void ADroperCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	SetupInputMappingContext();
}

void ADroperCharacter::UnPossessed()
{
	RemoveInputMappingContext();
	Super::UnPossessed();
}

void ADroperCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}

float ADroperCharacter::GetCurrentMoveSpeed() const
{
	return GetVelocity().Size();
}

// --------------------------------------------------
// Input Setup
// --------------------------------------------------

void ADroperCharacter::SetupInputMappingContext()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	if (Subsystem && DefaultMappingContext)
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ADroperCharacter::RemoveInputMappingContext()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	if (Subsystem && DefaultMappingContext)
	{
		Subsystem->RemoveMappingContext(DefaultMappingContext);
	}
}

void ADroperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!EIC) return;

	// Movement
	if (IA_Move) EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ADroperCharacter::HandleMove);
	if (IA_Look) EIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ADroperCharacter::HandleLook);
	if (IA_Jump) EIC->BindAction(IA_Jump, ETriggerEvent::Started, this, &ADroperCharacter::HandleJump);
	if (IA_Crouch) EIC->BindAction(IA_Crouch, ETriggerEvent::Started, this, &ADroperCharacter::HandleCrouch);
	if (IA_Prone) EIC->BindAction(IA_Prone, ETriggerEvent::Started, this, &ADroperCharacter::HandleProne);
	if (IA_Sprint)
	{
		EIC->BindAction(IA_Sprint, ETriggerEvent::Started, this, &ADroperCharacter::HandleSprintStarted);
		EIC->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &ADroperCharacter::HandleSprintCompleted);
	}

	// Combat
	if (IA_Fire)
	{
		EIC->BindAction(IA_Fire, ETriggerEvent::Started, this, &ADroperCharacter::HandleFireStarted);
		EIC->BindAction(IA_Fire, ETriggerEvent::Completed, this, &ADroperCharacter::HandleFireCompleted);
	}
	if (IA_ADS)
	{
		EIC->BindAction(IA_ADS, ETriggerEvent::Started, this, &ADroperCharacter::HandleADSStarted);
		EIC->BindAction(IA_ADS, ETriggerEvent::Completed, this, &ADroperCharacter::HandleADSCompleted);
	}
	if (IA_Reload) EIC->BindAction(IA_Reload, ETriggerEvent::Started, this, &ADroperCharacter::HandleReload);
	if (IA_SwitchWeapon) EIC->BindAction(IA_SwitchWeapon, ETriggerEvent::Triggered, this, &ADroperCharacter::HandleSwitchWeapon);
	if (IA_SwitchFireMode) EIC->BindAction(IA_SwitchFireMode, ETriggerEvent::Started, this, &ADroperCharacter::HandleSwitchFireMode);

	// Lean
	if (IA_LeanLeft)
	{
		EIC->BindAction(IA_LeanLeft, ETriggerEvent::Started, this, &ADroperCharacter::HandleLeanLeftStarted);
		EIC->BindAction(IA_LeanLeft, ETriggerEvent::Completed, this, &ADroperCharacter::HandleLeanLeftCompleted);
	}
	if (IA_LeanRight)
	{
		EIC->BindAction(IA_LeanRight, ETriggerEvent::Started, this, &ADroperCharacter::HandleLeanRightStarted);
		EIC->BindAction(IA_LeanRight, ETriggerEvent::Completed, this, &ADroperCharacter::HandleLeanRightCompleted);
	}

	// Interaction & Vault
	if (IA_Interact) EIC->BindAction(IA_Interact, ETriggerEvent::Started, this, &ADroperCharacter::HandleInteract);
	if (IA_Vault) EIC->BindAction(IA_Vault, ETriggerEvent::Started, this, &ADroperCharacter::HandleVault);
	if (IA_Scroll) EIC->BindAction(IA_Scroll, ETriggerEvent::Triggered, this, &ADroperCharacter::HandleScroll);

	// Gadgets & Utility
	if (IA_Gadget1) EIC->BindAction(IA_Gadget1, ETriggerEvent::Started, this, &ADroperCharacter::HandleGadget1);
	if (IA_Gadget2) EIC->BindAction(IA_Gadget2, ETriggerEvent::Started, this, &ADroperCharacter::HandleGadget2);
	if (IA_Inventory) EIC->BindAction(IA_Inventory, ETriggerEvent::Started, this, &ADroperCharacter::HandleInventory);
	if (IA_Ping) EIC->BindAction(IA_Ping, ETriggerEvent::Started, this, &ADroperCharacter::HandlePing);
	if (IA_VoiceChat)
	{
		EIC->BindAction(IA_VoiceChat, ETriggerEvent::Started, this, &ADroperCharacter::HandleVoiceChatStarted);
		EIC->BindAction(IA_VoiceChat, ETriggerEvent::Completed, this, &ADroperCharacter::HandleVoiceChatCompleted);
	}
}

// --------------------------------------------------
// Input Handlers
// --------------------------------------------------

void ADroperCharacter::HandleMove(const FInputActionValue& Value)
{
	const FVector2D MoveInput = Value.Get<FVector2D>();

	const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);
	const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDir, MoveInput.Y);
	AddMovementInput(RightDir, MoveInput.X);
}

void ADroperCharacter::HandleLook(const FInputActionValue& Value)
{
	const FVector2D LookInput = Value.Get<FVector2D>();
	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}

void ADroperCharacter::HandleFireStarted()
{
	if (EquipmentComp)
	{
		// EquipmentComp->StartFiring();
	}
	Server_Fire();
}

void ADroperCharacter::HandleFireCompleted()
{
	if (EquipmentComp)
	{
		// EquipmentComp->StopFiring();
	}
}

void ADroperCharacter::HandleADSStarted()
{
	bIsADS = true;
	Server_SetADS(true);
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
}

void ADroperCharacter::HandleADSCompleted()
{
	bIsADS = false;
	Server_SetADS(false);
	GetCharacterMovement()->MaxWalkSpeed = bIsSprinting ? 600.0f : 450.0f;
}

void ADroperCharacter::HandleReload()
{
	Server_Reload();
}

void ADroperCharacter::HandleSprintStarted()
{
	if (StaminaComp && StaminaComp->GetCurrentStamina() > 0.0f)
	{
		bIsSprinting = true;
		Server_SetSprinting(true);
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;

		// Cancel ADS when sprinting
		if (bIsADS)
		{
			HandleADSCompleted();
		}
	}
}

void ADroperCharacter::HandleSprintCompleted()
{
	bIsSprinting = false;
	Server_SetSprinting(false);
	GetCharacterMovement()->MaxWalkSpeed = 450.0f;
}

void ADroperCharacter::HandleCrouch()
{
	if (bIsCrouched)
	{
		UnCrouch();
	}
	else
	{
		Crouch();
		bIsSprinting = false;
	}
}

void ADroperCharacter::HandleProne()
{
	bIsProne = !bIsProne;
	if (bIsProne)
	{
		Crouch();
		GetCharacterMovement()->MaxWalkSpeed = 80.0f;
		bIsSprinting = false;
	}
	else
	{
		UnCrouch();
		GetCharacterMovement()->MaxWalkSpeed = 450.0f;
	}
}

void ADroperCharacter::HandleJump()
{
	if (!bIsProne)
	{
		Jump();
	}
}

void ADroperCharacter::HandleLeanLeftStarted()
{
	if (LeanComp) LeanComp->StartLeanLeft();
}

void ADroperCharacter::HandleLeanLeftCompleted()
{
	if (LeanComp) LeanComp->StopLean();
}

void ADroperCharacter::HandleLeanRightStarted()
{
	if (LeanComp) LeanComp->StartLeanRight();
}

void ADroperCharacter::HandleLeanRightCompleted()
{
	if (LeanComp) LeanComp->StopLean();
}

void ADroperCharacter::HandleInteract()
{
	if (InteractionComp) InteractionComp->TryInteract();
}

void ADroperCharacter::HandleVault()
{
	if (VaultComp) VaultComp->TryVault();
}

void ADroperCharacter::HandleInventory()
{
	// Toggle inventory UI — handled by HUD
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		// PC->ToggleInventory();
	}
}

void ADroperCharacter::HandleScroll(const FInputActionValue& Value)
{
	const float ScrollValue = Value.Get<float>();
	// Used for door graduation (scroll to open door gradually)
	if (InteractionComp)
	{
		InteractionComp->ApplyScrollInput(ScrollValue);
	}
}

void ADroperCharacter::HandleSwitchWeapon(const FInputActionValue& Value)
{
	const float Direction = Value.Get<float>();
	if (EquipmentComp)
	{
		if (Direction > 0.0f)
			EquipmentComp->SwitchToNextWeapon();
		else
			EquipmentComp->SwitchToPreviousWeapon();
	}
}

void ADroperCharacter::HandleSwitchFireMode()
{
	if (EquipmentComp)
	{
		EquipmentComp->SwitchFireMode();
	}
}

void ADroperCharacter::HandleGadget1()
{
	if (EquipmentComp) EquipmentComp->EquipGadget(0);
}

void ADroperCharacter::HandleGadget2()
{
	if (EquipmentComp) EquipmentComp->EquipGadget(1);
}

void ADroperCharacter::HandlePing()
{
	// Contextual ping — trace from camera and place world marker
}

void ADroperCharacter::HandleVoiceChatStarted()
{
	// ActivatePushToTalk
}

void ADroperCharacter::HandleVoiceChatCompleted()
{
	// DeactivatePushToTalk
}

// --------------------------------------------------
// Server RPCs
// --------------------------------------------------

void ADroperCharacter::Server_SetSprinting_Implementation(bool bSprint)
{
	bIsSprinting = bSprint;
}

void ADroperCharacter::Server_SetADS_Implementation(bool bAiming)
{
	bIsADS = bAiming;
}

void ADroperCharacter::Server_Fire_Implementation()
{
	// Server-side fire validation
}

void ADroperCharacter::Server_Reload_Implementation()
{
	// Server-side reload validation
}
