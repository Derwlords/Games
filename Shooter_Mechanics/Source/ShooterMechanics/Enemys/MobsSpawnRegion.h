// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MobsSpawnRegion.generated.h"

UCLASS()
class SHOOTERMECHANICS_API AMobsSpawnRegion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMobsSpawnRegion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:

	void SpawnEnemy();
	void SpawnBoss();

	UPROPERTY(EditAnywhere, Category = Enemy)
	TSubclassOf<class AEnemy> Enemy;
	UPROPERTY(EditAnywhere, Category = Enemy)
	TSubclassOf<class ABoss> Boss;


	UPROPERTY(EditAnywhere, Category = Health)
	TSubclassOf<APawn> Heal;
	UPROPERTY(EditAnywhere, Category = RandSpawn)
	float Spawn_X_Min;
	UPROPERTY(EditAnywhere, Category = RandSpawn)
	float Spawn_X_Max;
	UPROPERTY(EditAnywhere, Category = RandSpawn)
	float Spawn_Y_Min;
	UPROPERTY(EditAnywhere, Category = RandSpawn)
	float Spawn_Y_Max;
	UPROPERTY(EditAnywhere, Category = RandSpawn)
	float Spawn_Z_Enemy;

	UPROPERTY(EditAnywhere, Category = Enemy)
	int32 MaxEnemySpawnAtOneTime;

	FRotator SpawnRotation;
};
