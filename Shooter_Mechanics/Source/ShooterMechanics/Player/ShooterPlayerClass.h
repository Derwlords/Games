// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ShooterMechanics/BaseCharacter/BaseCharacter.h"
#include "ShooterPlayerClass.generated.h"

class AGrenade;
class UPlayerMovementComponent;
class USpringArmComponent;
UCLASS()
class SHOOTERMECHANICS_API  AShooterPlayerClass : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterPlayerClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;




	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser
	) override;
	UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
		void SwitchWeaponMesh(int32 index);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Items")
		bool IsOverlappingItem;

	UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
	void TriggerOutOfAmmoPopUp();

	UPROPERTY( BlueprintReadWrite, Category = HUD)
		UUserWidget* Player_HUD;

	

	UPROPERTY(VisibleAnywhere,Category = Grenade)
		AGrenade* Grenade;

	UPROPERTY(EditDefaultsOnly, Category = Grenade)
		UAnimMontage* GrenadeMontage;

	UPROPERTY(EditDefaultsOnly, Category = Grenade)
		UAnimMontage* TossGrenadeMontage;



	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Health)
		class UWeaponComponent* WeaponComponent;

	FORCEINLINE	USpringArmComponent* GetSpringArmComponent() {return SpringArm;}
	FORCEINLINE UPlayerMovementComponent* GetPLayerMovementComponent() { return PlayerMovementComponent; }

private:
	UPROPERTY(EditDefaultsOnly, Category = Camera)
		class USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, Category = Camera)
		class UCameraComponent* Camera;


	UPROPERTY(EditDefaultsOnly, Category = Rate)
		float TurnRate = 30.f;

	UPROPERTY(EditDefaultsOnly, Category = Rate)
		float LookUpRate = 30.f;


	

	UPROPERTY(EditDefaultsOnly, Category = HUD)
		TSubclassOf<class UUserWidget> HUD;
	
	
	
	

	/*UPROPERTY(EditDefaultsOnly, Category = Gun)
		TArray<AGun*> Weapons;*/

	

	UPROPERTY(EditDefaultsOnly, Category = Grenade)
		TSubclassOf<AGrenade> Grenadeclass;

	UFUNCTION(BlueprintCallable,Category = Grenade)
		void ThrowGrenade();

	
	

	
	FTimerHandle SprintTimer;
	
	
	FTimerHandle GrenadeToss;


	int32 WeaponIndex;
	
	void LookUp(float value);
	void Turn(float value);
	void MoveForward(float value);
	void MoveRight(float value);

	void StartFire();

	void StopFire();
	

	
	
	void SwitchToNextPrimaryWeapon();
	void EquipItem();

	void Zoom();
	void StopZoom();

	void ChangeFireMode();
	
	void HoldGreande();
	void GrenadeTossMontage();
	void ShowGun();



	

	UPROPERTY(VisibleDefaultsOnly)
	UPlayerMovementComponent* PlayerMovementComponent;

	void Sprint();



	void OnStartReload();




	virtual void Death() override;
};
