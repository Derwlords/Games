// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SHOOTERMECHANICS_API  AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTriger();

	UPROPERTY(EditAnywhere, Category = AttackRRange)
		float Damage = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	 int32 MaxTotalAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		int32 MaxClipAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		int32 TotalAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		int32 ClipAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		float ReloadTime;



private:

	UPROPERTY(EditAnywhere, Category = Mesh)
		USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = Particle)
		UParticleSystem* ParticleSystem;

	UPROPERTY(EditDefaultsOnly, Category = Particle)
		UParticleSystem* HitEffect;

	bool GunTrace(FHitResult& HitResult, FVector& ShotDirection);

	AController* OwnerController()const;
	UPROPERTY(EditAnywhere, Category = AttackRRange)
		float MaxRange = 5000.f;

	UPROPERTY(EditAnywhere, Category = Material)
		class UMaterialInterface* ShootDecalToSpawn;

	class ADecalActor* Decal;
	
	class AGrenade* Grenade;


	
};
