#pragma once

#include "CoreMinimal.h"
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
};
//------------------------------------------------------------------------------------------------------------
