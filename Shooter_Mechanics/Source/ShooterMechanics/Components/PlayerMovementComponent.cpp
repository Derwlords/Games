// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

// Sets default values for this component's properties
UPlayerMovementComponent::UPlayerMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	BaseWalkSpeed = 600.f;
	SprintSpeed = 1200.f;

}
// Called when the game starts
void UPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UPlayerMovementComponent::Sprint()
{
	if (MovementComponent->MaxWalkSpeed == BaseWalkSpeed)
	{
		MovementComponent->MaxWalkSpeed = SprintSpeed;
	}
	else
	{
		MovementComponent->MaxWalkSpeed = BaseWalkSpeed;

	}
}

void UPlayerMovementComponent::BaseWalk()
{
	MovementComponent->MaxWalkSpeed = BaseWalkSpeed;
}


void UPlayerMovementComponent::MoveForward(float value)
{
	APawn* PlayerPawn = Cast<APawn>(GetOwner());
	PlayerPawn->AddMovementInput(GetOwner()->GetActorForwardVector(), value);
}


void UPlayerMovementComponent::MoveRight(float value)
{
	APawn* PlayerPawn = Cast<APawn>(GetOwner());
	PlayerPawn->AddMovementInput(GetOwner()->GetActorRightVector(), value);
}

void UPlayerMovementComponent::SetPlayerMovementComponent(UCharacterMovementComponent* PlayerMovement)
{
	MovementComponent = PlayerMovement;
}

void UPlayerMovementComponent::SetPlayerSpeed(float Speed) 
{ 
	MovementComponent->MaxWalkSpeed = Speed; 
}

