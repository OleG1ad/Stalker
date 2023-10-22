// Copyright Epic Games, Inc. All Rights Reserved.

#include "Stalker_Character.h"
#include "Stalker_Projectile.h"
#include "AWeapon.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

// AStalker_Character
//------------------------------------------------------------------------------------------------------------
AStalker_Character::AStalker_Character()
{
	// Character doesnt have a rifle at start
	Has_Rifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.0f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.0f, 0.0f, 60.0f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh_1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh_1P->SetOnlyOwnerSee(true);
	Mesh_1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh_1P->bCastDynamicShadow = false;
	Mesh_1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh_1P->SetRelativeLocation(FVector(-30.0f, 0.0f, -150.0f));
}
//------------------------------------------------------------------------------------------------------------
void AStalker_Character::Pickup_Weapon(AWeapon *weapon)
{
	// Check that the character is valid, and has no rifle yet
	if (weapon == 0 || Has_Rifle)
		return;

	if (Current_Weapon != 0)
	Current_Weapon->Detach();

	Current_Weapon = weapon;
	// Attach the weapon to the First Person Character
	FAttachmentTransformRules attachment_rules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Mesh_1P, attachment_rules, FName(TEXT("GripPoint")));
	
	Has_Rifle = true; 	// switch Has_Rifle so the animation blueprint can switch to another animation set
}
//------------------------------------------------------------------------------------------------------------
void AStalker_Character::BeginPlay()
{
	Super::BeginPlay(); // Call the base class  

	// Add Input Mapping Context
	if (APlayerController *player_controller = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem *input_subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(player_controller->GetLocalPlayer()))
			input_subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}
//------------------------------------------------------------------------------------------------------------
void AStalker_Character::SetupPlayerInputComponent(UInputComponent *player_input_component)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(player_input_component))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AStalker_Character::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AStalker_Character::Look);
		EnhancedInputComponent->BindAction(Fire_Action, ETriggerEvent::Triggered, this, &AStalker_Character::Fire);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}
//------------------------------------------------------------------------------------------------------------
void AStalker_Character::Move(const FInputActionValue &value)
{
	// input is a Vector2D
	FVector2D movement_vector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{// add movement 
		
		AddMovementInput(GetActorForwardVector(), movement_vector.Y);
		AddMovementInput(GetActorRightVector(), movement_vector.X);
	}
}
//------------------------------------------------------------------------------------------------------------
void AStalker_Character::Look(const FInputActionValue &value)
{
	// input is a Vector2D
	FVector2D look_axis_vector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{// add yaw and pitch input to controller
		
		AddControllerYawInput(look_axis_vector.X);
		AddControllerPitchInput(look_axis_vector.Y);
	}
}
//------------------------------------------------------------------------------------------------------------
void AStalker_Character::Fire(const FInputActionValue &value)
{
	if (Current_Weapon != 0)
		Current_Weapon->Fire(this);
}
//------------------------------------------------------------------------------------------------------------