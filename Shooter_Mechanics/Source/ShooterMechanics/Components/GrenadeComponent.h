// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GrenadeComponent.generated.h"

class AGrenade;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERMECHANICS_API UGrenadeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrenadeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintCallable, Category = Grenade)
	void ThrowGrenade();

	UPROPERTY(VisibleAnywhere, Category = Grenade)
	AGrenade* Grenade;

	UPROPERTY(EditDefaultsOnly, Category = Grenade)
	UAnimMontage* GrenadeMontage;

	UPROPERTY(EditDefaultsOnly, Category = Grenade)
	UAnimMontage* TossGrenadeMontage;

	void HoldGrenade();
	void GrenadeToss();

private:
	class AShooterPlayerClass* Player;

	UPROPERTY(EditDefaultsOnly, Category = Grenade)
	TSubclassOf<AGrenade> Grenadeclass;

	FTimerHandle GrenadeTossTimerHandle;

	

	void ShowGun();
};