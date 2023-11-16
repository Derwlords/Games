// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerMovementComponent.generated.h"

class UCharacterMovementComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERMECHANICS_API  UPlayerMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	
		
	void SetPlayerMovementComponent(UCharacterMovementComponent* PlayerMovement);
	void SetPlayerSpeed(float value);


	void Sprint();


	 void BaseWalk();


	void MoveForward(float value);
	void MoveRight(float value); 

private:

	UPROPERTY(EditDefaultsOnly, Category = "Walk Speed")
	float BaseWalkSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Walk Speed")
	float SprintSpeed;

	UPROPERTY(VisibleDefaultsOnly)
	UCharacterMovementComponent* MovementComponent;
	

};
