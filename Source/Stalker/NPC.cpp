#include "NPC.h"

//ANPC
//------------------------------------------------------------------------------------------------------------
// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
//------------------------------------------------------------------------------------------------------------
// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}
//------------------------------------------------------------------------------------------------------------
// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//------------------------------------------------------------------------------------------------------------



//ANPC_Human
//------------------------------------------------------------------------------------------------------------
void ANPC_Human::Attach_Weapon(USkeletalMeshComponent* character_mesh, FName arm_socket_name, AWeapon* weapon)
{
	// Check that the character is valid, and has no rifle yet
	if (weapon == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%S] >>>>> weapon == 0"), __FUNCTION__);
		return;
	}

	if (Current_Weapon != 0)
		Current_Weapon->Detach();

	Current_Weapon = weapon;
	Current_Weapon->Attach_To_Socket(character_mesh, arm_socket_name);
}
//------------------------------------------------------------------------------------------------------------