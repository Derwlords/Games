// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameMode.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "EngineUtils.h"
AShooterGameMode::AShooterGameMode()
{
	PrimaryActorTick.bCanEverTick = true;


}
void AShooterGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	EndGame();
}
void AShooterGameMode::BeginPlay()
{
	Super::BeginPlay();
	
}


void AShooterGameMode::EndGame()
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == true;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}

	
}

