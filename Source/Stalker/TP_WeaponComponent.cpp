#include "TP_WeaponComponent.h"
#include "Stalker_Character.h"
#include "Stalker_Projectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

//------------------------------------------------------------------------------------------------------------
UTP_WeaponComponent::UTP_WeaponComponent() // Sets default values for this component's properties
{
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f); 	// Default offset from the character location for projectiles to spawn
}
//------------------------------------------------------------------------------------------------------------
void UTP_WeaponComponent::AttachWeapon(AStalker_Character* target_character)
{
	Character = target_character;

	// Check that the character is valid, and has no rifle yet
	if (Character == 0 || Character->Has_Rifle)
		return;

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules attachment_rules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->Mesh_1P, attachment_rules, FName(TEXT("GripPoint")));
	
	Character->Has_Rifle = true; 	// switch Has_Rifle so the animation blueprint can switch to another animation set

	// Set up action bindings
	if (APlayerController* player_controller = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* input_subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(player_controller->GetLocalPlayer()))
			input_subsystem->AddMappingContext(FireMappingContext, 1);

		if (UEnhancedInputComponent* enhanced_input_component = Cast<UEnhancedInputComponent>(player_controller->InputComponent)) // Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			enhanced_input_component->BindAction(FireAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Fire);	// Fire
	}
}
//------------------------------------------------------------------------------------------------------------
void UTP_WeaponComponent::Fire()
{
	if (Character == 0 || Character->GetController() == 0)
		return;

	// Try and fire a projectile
	if (ProjectileClass != 0)
	{
		if (UWorld *world = GetWorld())
		{
			APlayerController* player_controller = Cast<APlayerController>(Character->GetController());
			FRotator spawn_rotation = player_controller->PlayerCameraManager->GetCameraRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			FVector spawn_location = GetOwner()->GetActorLocation() + spawn_rotation.RotateVector(MuzzleOffset);
	
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
			world->SpawnActor<AStalker_Projectile>(ProjectileClass, spawn_location, spawn_rotation, ActorSpawnParams); // Spawn the projectile at the muzzle

		}
	}
	
	if (FireSound != 0)
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation()); 	// Try and play the sound if specified

	
	// Try and play a firing animation if specified
	if (FireAnimation != 0)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* anim_instance = Character->Mesh_1P->GetAnimInstance();
		if (anim_instance != 0)
			anim_instance->Montage_Play(FireAnimation, 1.f);
	}
}
//------------------------------------------------------------------------------------------------------------
void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type end_play_reason)
{
	if (Character == 0)
		return;

	if (APlayerController* player_controller = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* input_subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(player_controller->GetLocalPlayer()))
			input_subsystem->RemoveMappingContext(FireMappingContext);
	}
}
//------------------------------------------------------------------------------------------------------------
