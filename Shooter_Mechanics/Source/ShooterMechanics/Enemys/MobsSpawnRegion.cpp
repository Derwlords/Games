// Fill out your copyright notice in the Description page of Project Settings.


#include "MobsSpawnRegion.h"
#include "ShooterMechanics/Enemys/Enemy.h"
#include "ShooterMechanics/Enemys/Boss.h"
// Sets default values
AMobsSpawnRegion::AMobsSpawnRegion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Spawn_X_Min = -1000.f;
	Spawn_X_Max = 1000.f;

	Spawn_Y_Min = -1000.f;
	Spawn_Y_Max = 1000.f;
	
	Spawn_Z_Enemy = 194.f;

	MaxEnemySpawnAtOneTime = 5;
}

// Called when the game starts or when spawned
void AMobsSpawnRegion::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle Enemy_bot;
	GetWorldTimerManager().SetTimer(Enemy_bot, this, &AMobsSpawnRegion::SpawnEnemy, FMath::RandRange(5, 10), true, 1);
	/*FTimerHandle EnemyBoss;
	GetWorldTimerManager().SetTimer(EnemyBoss, this, &AMobsSpawnRegion::SpawnBoss, FMath::RandRange(30, 60), true, 30);*/
}

// Called every frame
void AMobsSpawnRegion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMobsSpawnRegion::SpawnEnemy()
{



	SpawnRotation = FRotator(0.f, 0.f, 0.f);

	for (int32 counter = FMath::RandRange(1, MaxEnemySpawnAtOneTime); counter <= MaxEnemySpawnAtOneTime; counter++)
	{
		float RandX = FMath::RandRange(Spawn_X_Min, Spawn_X_Max);
		float RandY = FMath::RandRange(Spawn_Y_Min, Spawn_Y_Max);

		FVector SpawnPosition = FVector(RandX, RandY, Spawn_Z_Enemy);
		GetWorld()->SpawnActor(Enemy, &SpawnPosition, &SpawnRotation);
	}

}

void AMobsSpawnRegion::SpawnBoss()
{
	FVector SpawnPosition = FVector(0.f, 0.f, Spawn_Z_Enemy);
	GetWorld()->SpawnActor(Boss, &SpawnPosition, &SpawnRotation);
}