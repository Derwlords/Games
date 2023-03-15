// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class SHOOTER_MECHANICS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
private:
	UPROPERTY(EditAnywhere)
		float damage = 25.f;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class USphereComponent* CollisionSphare;

	UPROPERTY(VisibleDefaultsOnly, Category = Movement)
	class UProjectileMovementComponent* ProjectileMevement;
	UPROPERTY(EditAnywhere, Category = Material)
		class UMaterialInterface* ShootDecalToSpawn;
	class ADecalActor* Decal;
};
