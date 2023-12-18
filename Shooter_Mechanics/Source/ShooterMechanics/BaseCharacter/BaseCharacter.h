// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UHealthComponent;

UCLASS()
class SHOOTERMECHANICS_API ABaseCharacter : public ACharacter
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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Health)
	UHealthComponent* HealthComponent;

	virtual void Death();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Points")
	int32 Points;

	FORCEINLINE UHealthComponent* GetHealthComponent() { return HealthComponent; }

protected:



	FTimerHandle DeathTimer;

	UPROPERTY(EditDefaultsOnly,Category = "Death")
	float TimeUntilDestroy;



	
};
