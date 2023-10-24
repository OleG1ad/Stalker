#include "AWeapon.h"
#include "Kismet/GameplayStatics.h"

//------------------------------------------------------------------------------------------------------------
AWeapon::AWeapon()
{
 	Muzzle_Offset = FVector(100.0f, 0.0f, 10.0f); 	// Default offset from the character location for projectiles to spawn

}
//------------------------------------------------------------------------------------------------------------
void AWeapon::Attach(USkeletalMeshComponent *arms_mesh)
{
	USceneComponent *root_component = GetRootComponent();

	if (UPrimitiveComponent *prim_component = Cast<UPrimitiveComponent>(root_component))
	{
		prim_component->SetSimulatePhysics(false);
		prim_component->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	}
	
	// Attach the weapon to the First Person Character
	FAttachmentTransformRules attachment_rules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(arms_mesh, attachment_rules, FName(TEXT("GripPoint")));
}
//------------------------------------------------------------------------------------------------------------
void AWeapon::Detach()
{
	USceneComponent *root_component = GetRootComponent();
	
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	if (UPrimitiveComponent *prim_component = Cast<UPrimitiveComponent>(root_component))
	{
		prim_component->SetSimulatePhysics(true);
		prim_component->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	}
}
//------------------------------------------------------------------------------------------------------------
void AWeapon::Fire(AStalker_Character *character)
{
	if (character == 0 || character->GetController() == 0)
		return;

	// Try and fire a projectile
	if (Projectile_Class != 0)
	{
		if (UWorld *world = GetWorld())
		{
			APlayerController* player_controller = Cast<APlayerController>(character->GetController());
			FRotator spawn_rotation = player_controller->PlayerCameraManager->GetCameraRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			FVector spawn_location = GetActorLocation() + spawn_rotation.RotateVector(Muzzle_Offset);
	
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
			world->SpawnActor<AStalker_Projectile>(Projectile_Class, spawn_location, spawn_rotation, ActorSpawnParams); // Spawn the projectile at the muzzle

		}
	}
	
	if (Fire_Sound != 0)
		UGameplayStatics::PlaySoundAtLocation(this, Fire_Sound, character->GetActorLocation()); 	// Try and play the sound if specified

	
	// Try and play a firing animation if specified
	if (Fire_Animation != 0)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* anim_instance = character->Mesh_1P->GetAnimInstance();
		if (anim_instance != 0)
			anim_instance->Montage_Play(Fire_Animation, 1.f);
	}
}
//------------------------------------------------------------------------------------------------------------
