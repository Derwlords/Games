// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grenade.generated.h"

UCLASS()
class SHOOTER_MECHANICS_API AGrenade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrenade();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* GrenadeMesh;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
		class UAnimationAsset* ThrowAnimation;

	


	UPROPERTY(EditDefaultsOnly, Category = Grenade)
		float FuseLenght;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnReleased(FVector ForwardVector);

	void Explode();


	UPROPERTY(EditDefaultsOnly, Category = Grenade)
		class USphereComponent* DamageSphere;
private:


	UPROPERTY(EditDefaultsOnly, Category = Grenade)
		float GrenadeDamage = 60.f;

	UPROPERTY(EditDefaultsOnly, Category = Grenade)
		float GrenadeTossImpulse = 2500.f;

};
