#pragma once

#include "AWeapon.h"
#include "GameFramework/Character.h"
#include "NPC.generated.h"
//------------------------------------------------------------------------------------------------------------
UCLASS()
class STALKER_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
//------------------------------------------------------------------------------------------------------------
UCLASS()
class STALKER_API ANPC_Human : public ANPC
{
	GENERATED_BODY()

	public:
	UFUNCTION(BlueprintCallable, Category="Weapon") void Attach_Weapon(USkeletalMeshComponent* character_mesh, FName arm_socket_name, AWeapon* weapon);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Stalker) AWeapon* Current_Weapon = 0;
};
//------------------------------------------------------------------------------------------------------------
