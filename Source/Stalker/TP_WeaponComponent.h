#pragma once

#include "Stalker_Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "TP_WeaponComponent.generated.h"

//------------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STALKER_API UTP_WeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	UTP_WeaponComponent(); 	/** Sets default values for this component's properties */

	UFUNCTION(BlueprintCallable, Category="Weapon") void AttachWeapon(AStalker_Character* target_character); 	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon") void Fire(); // Make the weapon Fire a Projectile

	UPROPERTY(EditDefaultsOnly, Category=Projectile) TSubclassOf<class AStalker_Projectile> ProjectileClass; // Projectile class to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay) USoundBase* FireSound; 	// Sound to play each time we fire
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) UAnimMontage* FireAnimation; // AnimMontage to play each time we fire
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay) FVector MuzzleOffset; // Gun muzzle's offset from the characters location
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true")) UInputMappingContext* FireMappingContext; 	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true")) UInputAction* FireAction; 	/** Fire Input Action */

protected:
	/** Ends gameplay for this component. */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type end_play_reason) override;

private:
	/** The Character holding this weapon*/
	AStalker_Character* Character;
};
//------------------------------------------------------------------------------------------------------------
