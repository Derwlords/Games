// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Shooter/BaseCharacter/BaseCharacter.h"
#include "ShooterPlayer.generated.h"


class UCameraComponent;
class USpringArmComponent;


UCLASS()
class SHOOTER_API AShooterPlayer : public  ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterPlayer();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera)
		UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = SpringArm)
		USpringArmComponent* SpringArm;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerControll)
		bool bClimbing;

	UFUNCTION(BlueprintCallable, Category = MoveSpeed)
		virtual void MoveForward(float value);

	UFUNCTION(BlueprintCallable, Category = MoveSpeed)
		virtual void MoveRight(float value);
private:
	
	UCapsuleComponent* Capsule;
	UCharacterMovementComponent* Movement;
	
	UPROPERTY(EditDefaultsOnly, Category = MoveSpeed)
		float TakeAimSpeed;

	void StartTakeAim();
	void StopTakeAim();



	UPROPERTY(EditDefaultsOnly, Category = PlayerControll)
	float LookUpRate;

	UPROPERTY(EditDefaultsOnly, Category = PlayerControll)
	float TurnRate;

	

	void Turn(float value);
	void LookUp(float value);

	void GrenadeThrow();


	virtual void Jump();
	virtual void StopJumping();

	bool ClimbingTrace(FHitResult& HitResult);
	void StartClimbing();
	void StopClimbing();

	UPROPERTY(EditDefaultsOnly, Category = MoveSpeed)
		float ClimbingSpeed;

	
};
