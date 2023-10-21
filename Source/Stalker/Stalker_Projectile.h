#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Stalker_Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
//------------------------------------------------------------------------------------------------------------
UCLASS(config = Game)
class AStalker_Projectile : public AActor
{
	GENERATED_BODY()

public:
	AStalker_Projectile();
	
	UFUNCTION() void On_Hit(UPrimitiveComponent *hit_comp, AActor *other_actor, UPrimitiveComponent *other_comp, FVector normal_impulse, const FHitResult& hit); /** called when projectile hits something */

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile) USphereComponent *Collision_Comp; /** Sphere collision component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true")) UProjectileMovementComponent *Projectile_Movement; /** Projectile movement component */
};
//------------------------------------------------------------------------------------------------------------
// UCLASS(config = Game)
// class AStalkerProjectile : public AStalker_Projectile
// {
// 	GENERATED_BODY()
// };
//------------------------------------------------------------------------------------------------------------
