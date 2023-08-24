// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class AGrenade;
class AAK47;
class ABaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void HoldGrenade();
	void ThrowGrenade();
	
	
private:
	
	UPROPERTY(EditDefaultsOnly, Category = Grenade)
	TSubclassOf<AGrenade> GrenadeClass;
	
	UPROPERTY(EditDefaultsOnly, Category = Grenade)
		UAnimMontage* TossGrenadeMontage;

	UPROPERTY(EditDefaultsOnly, Category = Grenade)
	float ThrowDelay;

	AGrenade* Grenade;

	//Grenade timer
	FTimerHandle GrenadeToss;

	

	//Delay until weapon display after throwing a grenade
	UPROPERTY(EditDefaultsOnly, Category = Grenade)
	float ShowWeaponDelay;

	FTimerHandle ShowFirstWeapon;

	void ShowWeapon();

	//Player's main weapon
	UPROPERTY(EditDefaultsOnly, Category = Gun)
	TSubclassOf<AAK47> FirstWeaponClass;

	AAK47* FirstWeapon;
	
	ABaseCharacter* Player;


	
};