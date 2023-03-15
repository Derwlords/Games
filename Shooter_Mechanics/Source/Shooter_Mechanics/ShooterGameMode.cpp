// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameMode.h"
#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "Boss.h"
void AShooterGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AShooterGameMode::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle Enemy_bot;
	GetWorldTimerManager().SetTimer(Enemy_bot,this, &AShooterGameMode::SpawnEnemy, FMath::RandRange(5, 10), true,1);
	FTimerHandle EnemyBoss;
	GetWorldTimerManager().SetTimer(EnemyBoss, this, &AShooterGameMode::SpawnBoss, FMath::RandRange(30, 60), true,30);
}
AShooterGameMode::AShooterGameMode()
{
}

void AShooterGameMode::SpawnHeal()
{


}

void AShooterGameMode::SpawnEnemy()
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

void AShooterGameMode::SpawnBoss()
{
	FVector SpawnPosition = FVector(0.f, 0.f, Spawn_Z_Enemy);
	GetWorld()->SpawnActor(Boss, &SpawnPosition, &SpawnRotation);
}
