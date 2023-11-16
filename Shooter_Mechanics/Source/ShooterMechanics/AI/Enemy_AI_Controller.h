// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy_AI_Controller.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERMECHANICS_API  AEnemy_AI_Controller : public AAIController
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame

	virtual void Tick(float DeltaTime) override;

private:
	APawn* Player;
	UPROPERTY(EditAnywhere)
		class UBehaviorTree* BehaviorTree;

};
