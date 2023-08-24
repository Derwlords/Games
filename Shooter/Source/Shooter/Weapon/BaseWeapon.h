// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

UCLASS()
class SHOOTER_API ABaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:

	UPROPERTY(EditAnywhere,Category = Mesh)
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere)
	USceneComponent* ProjectileSpawnPoint;

	//Ammo in clip at the moment
	UPROPERTY(EditAnywhere, Category = WeaponAttributes)
	int32 InClip;

	//Max ammo per magazine
	UPROPERTY(EditAnywhere, Category = WeaponAttributes)
	int32 MaxInClip;

	//The ammo that the player currently has
	UPROPERTY(EditAnywhere, Category = WeaponAttributes)
	int32 TotalAmmo;

	//The maximum amount of ammo a player can have
	UPROPERTY(EditAnywhere, Category = WeaponAttributes)
	int32 MaxTotalAmmo;

	//Reload Time
	UPROPERTY(EditAnywhere,Category = ReloadTime)
	float ReloadTime;

	UPROPERTY(EditAnywhere, Category = ReloadTime)
	float Damage;

	UPROPERTY(EditAnywhere, Category = ReloadTime)
	float MaxRange;


	void PullTriger();
	bool GunTrace(FHitResult& HitResult, FVector& ShotDicretion);
	AController* GetOwnerController();
};
