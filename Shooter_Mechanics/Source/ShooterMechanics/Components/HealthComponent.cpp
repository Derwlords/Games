// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "ShooterMechanics/Player/ShooterPlayerClass.h"
// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	
	Health = MaxHealth;
	Armor = MaxArmor;
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
void UHealthComponent::DealDamage(float Damage)
{
	Armor -= Damage;
	if (Armor < 0)
	{
		
		Health += Armor;
		Armor = 0;
	}
}

void UHealthComponent::IsDead() const
{
	if ( Health > 0)
	{
		return;
	}
	Cast<AShooterPlayerClass>(GetOwner())->Death();
}




