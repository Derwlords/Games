// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ShooterMechanics/BaseCharacter/BaseCharacter.h"
#include "ShooterPlayerClass.generated.h"


class UPlayerMovementComponent;
class USpringArmComponent;
class UWeaponComponent;
class UGrenadeComponent;
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

	




	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Health)
		class UWeaponComponent* WeaponComponent;

	FORCEINLINE	USpringArmComponent* GetSpringArmComponent() {return SpringArm;}
	FORCEINLINE UPlayerMovementComponent* GetPLayerMovementComponent() { return PlayerMovementComponent; }
	FORCEINLINE UWeaponComponent* GetWeaponComponent() { return WeaponComponent; }
private:
	UPROPERTY(EditDefaultsOnly, Category = Camera)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, Category = Camera)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly)
	UPlayerMovementComponent* PlayerMovementComponent;

	UPROPERTY(VisibleDefaultsOnly)
	UGrenadeComponent* GrenadeComponent;


		


	UPROPERTY(EditDefaultsOnly, Category = Rate)
		float TurnRate = 30.f;

	UPROPERTY(EditDefaultsOnly, Category = Rate)
		float LookUpRate = 30.f;


	

	UPROPERTY(EditDefaultsOnly, Category = HUD)
		TSubclassOf<class UUserWidget> HUD;
	
	
	
	

	/*UPROPERTY(EditDefaultsOnly, Category = Gun)
		TArray<AGun*> Weapons;*/

	

	

	

	
	FTimerHandle SprintTimer;
	
	
	


	int32 WeaponIndex;
	
	void LookUp(float value);
	void Turn(float value);

	void MoveForward(float value);
	void MoveRight(float value);

	void Sprint();


	void SwitchToNextPrimaryWeapon();
	void EquipItem();



	void Zoom();
	void StopZoom();

	void ChangeFireMode();

	void StartFire();
	void StopFire();

	void OnStartReload();

	
	

	void HoldGrenade();
	void GrenadeToss();


	virtual void Death() override;

	
};
