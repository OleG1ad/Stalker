#pragma once

#include "Stalker_Character.h"
#include "Stalker_Projectile.h"
#include "GameFramework/Actor.h"
#include "AWeapon.generated.h"

//------------------------------------------------------------------------------------------------------------
UCLASS()
class STALKER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();

	void Detach();

	UFUNCTION(BlueprintCallable, Category="Weapon") void Fire(AStalker_Character *character); // Make the weapon Fire a Projectile

	UPROPERTY(EditDefaultsOnly, Category=Projectile) TSubclassOf<class AStalker_Projectile> Projectile_Class; // Projectile class to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay) USoundBase* Fire_Sound; 	// Sound to play each time we fire
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) UAnimMontage* Fire_Animation; // AnimMontage to play each time we fire
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay) FVector Muzzle_Offset; // Gun muzzle's offset from the characters location
};
//------------------------------------------------------------------------------------------------------------
