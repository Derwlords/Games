// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
#include "ShooterPlayerClass.h"
#include "ShooterMechanics/Components/HealthComponent.h"

void AShooterPlayerController::BeginPlay()
{

	Super::BeginPlay();
   

    if (Cast<AShooterPlayerClass>(GetPawn()))
    {

       PlayerHUD = CreateWidget(this, HUDClass);
       PlayerHUD->AddToViewport();
    }
      

}

void AShooterPlayerController::Tick(float DeltaTime)
{

    Super::Tick(DeltaTime);
 
}


void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    if (Cast<AShooterPlayerClass>(GetPawn())->GetPlayerPoints() == 100  )
    {
        PlayerHUD->RemoveFromViewport();
        UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
        if (!WinScreen)
        {
            return;
        }
        WinScreen->AddToViewport();
     
    }
    else if(!bIsWinner)
    {
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
        if (!LoseScreen)
        {
            return;
        }
        LoseScreen->AddToViewport();
        PlayerHUD->RemoveFromViewport();
    }
}