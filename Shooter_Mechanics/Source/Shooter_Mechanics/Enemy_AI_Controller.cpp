// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_AI_Controller.h"
#include "Kismet/GameplayStatics.h"
#include "Shooter_Player_Class.h"
#include "BehaviorTree/BlackboardComponent.h"

void AEnemy_AI_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GetBlackboardComponent()->SetValueAsObject("Player", Player);
	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);

		Player = UGameplayStatics::GetPlayerPawn(this, 0);

	}
}

void AEnemy_AI_Controller::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);
	
}
