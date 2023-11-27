// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

class UUserWidget;
UCLASS()
class SHOOTERMECHANICS_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> WinScreenClass;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> LoseScreenClass;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> HUDClass;

	UPROPERTY(EditDefaultsOnly)
	float RestartDelay = 5;

	UUserWidget* PlayerHUD;


	
};
