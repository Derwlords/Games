// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameMode.h"
#include "GameFramework/Actor.h"
#include "ShooterMechanics/Player/ShooterPlayerCOntroller.h"
#include "EngineUtils.h"
#include "ShooterMechanics/AI/Enemy_AI_Controller.h"
AShooterGameMode::AShooterGameMode()
{
	PrimaryActorTick.bCanEverTick = true;


}
void AShooterGameMode::PawnKilled(APawn* PawnKilled)
{
    AShooterPlayerController* PlayerController = Cast<AShooterPlayerController>(PawnKilled->GetController());
    if (PlayerController)
    {
        EndGame(false);
    }

    for (AEnemy_AI_Controller* Controller : TActorRange<AEnemy_AI_Controller>(GetWorld()))
    {
        if (Controller->GetEnemyStatus())
        {
            return;
        }
    }

    EndGame(true);

}
void AShooterGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
void AShooterGameMode::BeginPlay()
{
	Super::BeginPlay();
	
}


void AShooterGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}

	
}

