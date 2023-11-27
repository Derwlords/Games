// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
#include "ShooterPlayerClass.h"
#include "ShooterMechanics/Components/HealthComponent.h"

void AShooterPlayerController::BeginPlay()
{

	Super::BeginPlay();
   

    PlayerHUD = CreateWidget(this, HUDClass);
    if (!PlayerHUD)
    {
        return;
    }
        PlayerHUD->AddToViewport();

      

}

void AShooterPlayerController::Tick(float DeltaTime)
{

    Super::Tick(DeltaTime);
 
}


void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    if (Cast<AShooterPlayerClass>(GetPawn())->GetPlayerPoints() == 100 && Cast<AShooterPlayerClass>(GetPawn())->GetHealthComponent()->Dead == false)
    {
        PlayerHUD->RemoveFromViewport();
        UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
        if (!WinScreen)
        {
            return;
        }
        WinScreen->AddToViewport();
     
    }
    else
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