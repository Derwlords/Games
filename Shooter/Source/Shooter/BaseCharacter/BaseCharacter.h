// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseCharacter.generated.h"


class UHealthComponent;
class UWeaponComponent;


UCLASS()
class SHOOTER_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void StartSprint();
	void StopSprint();

	
	
	
protected:

	virtual void MoveForward(float value);
	virtual void MoveRight(float value);

	UPROPERTY(EditDefaultsOnly,Category = Health)
	UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
		UWeaponComponent* WeaponComponent;


	UCharacterMovementComponent* CharacterMovment;

	UPROPERTY(EditDefaultsOnly, Category = MoveSpeed)
		float BaseWalkSpeed;

	UPROPERTY(EditDefaultsOnly, Category = MoveSpeed)
		float BackWalkSpeed;

	UPROPERTY(EditDefaultsOnly, Category = MoveSpeed)
		float SprintSpeed;

	UCharacterMovementComponent* GetCharacterMovmentComponent() { return CharacterMovment; }


	
};
