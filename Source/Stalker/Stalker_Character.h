#pragma once

// #include "AWeapon.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Stalker_Character.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class AWeapon;


DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

//------------------------------------------------------------------------------------------------------------
UCLASS(config = Game)
class AStalker_Character : public ACharacter
{
	GENERATED_BODY()

public:
	AStalker_Character();
	
	// USkeletalMeshComponent *Get_Mesh_1P() const;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh) USkeletalMeshComponent *Mesh_1P; 	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon) bool Has_Rifle; // Bool for AnimBP to switch to another animation set

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) AWeapon *Current_Weapon;

protected:
	virtual void BeginPlay();
	virtual void SetupPlayerInputComponent(UInputComponent *input_component);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TArray<AActor *> Interactable_Actors; //Items that player can interactable
	
private:
	void On_Action_Move(const FInputActionValue &value); /** Called for movement input */
	void On_Action_Look(const FInputActionValue &value); /** Called for looking input */
	void On_Action_Fire(const FInputActionValue &value);
	void On_Action_Use(const FInputActionValue &value);

	void Pickup_Weapon(AWeapon *weapon); //Attaches the actor to a FirstPersonCharacter

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true")) UCameraComponent *FirstPersonCameraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputMappingContext *DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputAction *Action_Jump;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputAction *Action_Move;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputAction *Action_Look;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputAction *Action_Fire;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputAction *Action_Use;
};
//------------------------------------------------------------------------------------------------------------
