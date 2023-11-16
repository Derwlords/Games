// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERMECHANICS_API  AShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AShooterGameMode();

private:
	void SpawnHeal();

	void SpawnEnemy();
	void SpawnBoss();
	UPROPERTY(EditAnywhere, Category = Enemy)
		TSubclassOf<class AEnemy> Enemy;
	UPROPERTY(EditAnywhere, Category = Enemy)
		TSubclassOf<class ABoss> Boss;

	UPROPERTY(EditAnywhere, Category = Health)
		TSubclassOf<APawn> Heal;
	UPROPERTY(EditAnywhere, Category = RandSpawn)
		float Spawn_X_Min = -1000.f;
	UPROPERTY(EditAnywhere, Category = RandSpawn)
		float Spawn_X_Max = 1000.f;
	UPROPERTY(EditAnywhere, Category = RandSpawn)
		float Spawn_Y_Min = -1000.f;
	UPROPERTY(EditAnywhere, Category = RandSpawn)
		float Spawn_Y_Max = 1000.f;
	UPROPERTY(EditAnywhere, Category = RandSpawn)
		float Spawn_Z_Enemy = 194.f;

	UPROPERTY(EditAnywhere, Category = Enemy)
		int32 MaxEnemySpawnAtOneTime = 5;

	FRotator SpawnRotation;




};
