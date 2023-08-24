// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grenade.generated.h"

class UAnimationAsset;
class USphereComponent;
UCLASS()
class SHOOTER_API AGrenade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrenade();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Explode();

	void OnReleased(FVector ForwardVector);

private:



	UPROPERTY(EditAnywhere, Category = Mesh)
		USkeletalMeshComponent* GrenadeMesh;

	UPROPERTY(EditDefaultsOnly, Category = Grenade)
		USphereComponent* DamageSphere;

	//UPROPERTY(EditDefaultsOnly, Category = Mesh)
	//UAnimationAsset* ThrowAnimation;


	UPROPERTY(EditDefaultsOnly, Category = Grenade)
	float FuseLenght;

	UPROPERTY(EditDefaultsOnly, Category = Grenade)
	float GrenadeDamage;

	UPROPERTY(EditDefaultsOnly, Category = Grenade)
	float GrenadeTossImpulse;
};
