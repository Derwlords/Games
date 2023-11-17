// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "ShooterMechanics/Components/HealthComponent.h"
// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateAbstractDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	TimeUntilDestroy = 1.f;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::DestroyCharacter()
{
	Destroy();
}

void ABaseCharacter::Death()
{
	if (HealthComponent->IsDead())
	{
		GetWorldTimerManager().SetTimer(DeathTimer, this, &ABaseCharacter::DestroyCharacter, TimeUntilDestroy, false);
	}
}
