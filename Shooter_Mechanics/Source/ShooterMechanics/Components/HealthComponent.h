// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERMECHANICS_API  UHealthComponent : public UActorComponent
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyHealth)
		float Health = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyHealth)
		float Armor = 0.f;

	float GetMaxHealth() { return MaxHealth; }
	float GetArmor() { return MaxArmor; }

	void DealDamage(float Damage);

	UFUNCTION(BlueprintPure)
	bool IsDead() const;


private:
	UPROPERTY(EditDefaultsOnly, Category = Health)
		float MaxHealth = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = Health)
		float MaxArmor = 100.f;

	
};
