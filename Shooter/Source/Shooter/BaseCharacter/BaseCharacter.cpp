// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "Shooter/Component/HealthComponent.h"
#include "Shooter/Component/WeaponComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>("WeaponComponent");


}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	

	CharacterMovment = GetCharacterMovement();
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);
	
}

void ABaseCharacter::MoveForward(float value)
{
	if (value < 0)
	{
		AddMovementInput(GetActorForwardVector(), value * BackWalkSpeed);
	}
	else
	{

		AddMovementInput(GetActorForwardVector(), value);
	}
}

void ABaseCharacter::MoveRight(float value)
{
	
		AddMovementInput(GetActorRightVector(), value );
	
}


void ABaseCharacter::StartSprint()
{
	CharacterMovment->MaxWalkSpeed = SprintSpeed;
}

void ABaseCharacter::StopSprint()
{
	CharacterMovment->MaxWalkSpeed = BaseWalkSpeed;
}