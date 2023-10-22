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

	UFUNCTION(BlueprintCallable) void Pickup_Weapon(AWeapon *weapon); //Attaches the actor to a FirstPersonCharacter
	
	// USkeletalMeshComponent *Get_Mesh_1P() const;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh) USkeletalMeshComponent *Mesh_1P; 	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputAction *LookAction;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon) bool Has_Rifle; // Bool for AnimBP to switch to another animation set

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) AWeapon *Current_Weapon;

protected:
	virtual void BeginPlay();
	virtual void SetupPlayerInputComponent(UInputComponent *input_component);
	
	void Move(const FInputActionValue &value); /** Called for movement input */
	void Look(const FInputActionValue &value); /** Called for looking input */
	void Fire(const FInputActionValue &value);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true")) UCameraComponent *FirstPersonCameraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputMappingContext *DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputAction *JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputAction *MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputAction *Fire_Action;
};
//------------------------------------------------------------------------------------------------------------
