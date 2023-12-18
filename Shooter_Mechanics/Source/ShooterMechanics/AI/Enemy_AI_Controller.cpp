// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_AI_Controller.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterMechanics/Player/ShooterPlayerClass.h"
#include "ShooterMechanics/Enemys/Enemy.h"
#include "ShooterMechanics/Components/HealthComponent.h"
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

bool AEnemy_AI_Controller::GetEnemyStatus()
{
	return Cast<AEnemy>(GetPawn())->GetHealthComponent()->Dead;
}

void AEnemy_AI_Controller::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);
	
}
