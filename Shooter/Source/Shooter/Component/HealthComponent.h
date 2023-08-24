// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float GetHealth() { return Health; }
	float GetArmor() { return Armor; }

	void ReduceHP(float value);

private:

	UPROPERTY(EditDefaultsOnly,Category = Health)
	float Health;

	UPROPERTY(EditDefaultsOnly, Category = Health)
	float Armor;


	UPROPERTY(EditDefaultsOnly, Category = Health)
	float MaxHealth;

	UPROPERTY(EditDefaultsOnly, Category = Health)
	float MaxArmor;





		
};
