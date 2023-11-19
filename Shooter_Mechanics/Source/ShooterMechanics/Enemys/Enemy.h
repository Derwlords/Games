// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShooterMechanics/BaseCharacter/BaseCharacter.h"
#include "Enemy.generated.h"

UCLASS()
class SHOOTERMECHANICS_API  AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;




	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser
	) override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
	
		UFUNCTION()
		void ClearTimer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
		
	UFUNCTION()
		void ApplyDamage();

	
		
private:


	UPROPERTY(EditAnywhere)
		float DamageValue = 10.f;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* DamageCollision;

	

	UPROPERTY()
	FTimerHandle TimerHandle;
	FTimerHandle EnemyDeathTimer;
	UPROPERTY()
	class AShooterPlayerClass* Player;
	bool PlayerInCollisionBox;
	bool PlayerInDamageCollision();
	

	virtual void Death() override;
	
};
