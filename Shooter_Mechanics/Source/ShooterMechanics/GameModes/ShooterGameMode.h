// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterGameMode.generated.h"

class UUserWidget;

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

	 void PawnKilled(APawn* PawnKilled) ;

private:
	

	
	
	
	
	void EndGame(bool bIsPlayerWinner);
	

	




};
