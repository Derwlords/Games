// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "Shooter_Player_Class.generated.h"

class AGrenade;

UCLASS()
class SHOOTER_MECHANICS_API AShooter_Player_Class : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooter_Player_Class();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyHealth)
		float Health = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyHealth)
		float Armor = 0.f;
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
		class AGun* Gun;

	UFUNCTION()
		void StartHorizontalRecoil(float value);
	UFUNCTION()
		void StartVerticalRecoil(float value);

	void StartRecoil();

	void EndRecoil();

	void PlayerDead();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Recoil")
		class UCurveFloat* VerticalCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Recoil")
		class UCurveFloat* HorizontalCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Reload)
		bool IsReloading;

	UPROPERTY(VisibleAnywhere,Category = Grenade)
		AGrenade* Grenade;

	UPROPERTY(EditDefaultsOnly, Category = Grenade)
		UAnimMontage* GrenadeMontage;

	UPROPERTY(EditDefaultsOnly, Category = Grenade)
		UAnimMontage* TossGrenadeMontage;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = Health)
		class UHealthComponent* HealthComponent;

	
private:
	UPROPERTY(EditDefaultsOnly, Category = Camera)
		class USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, Category = Camera)
		class UCameraComponent* Camera;


	UPROPERTY(EditDefaultsOnly, Category = Rate)
		float TurnRate = 30.f;

	UPROPERTY(EditDefaultsOnly, Category = Rate)
		float LookUpRate = 30.f;

	UPROPERTY(EditDefaultsOnly, Category = Health)
		float MaxHealth = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = Health)
		float MaxArmor = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "Shoot Timer")
		float TimeBetwenShoots;

	UPROPERTY(EditDefaultsOnly, Category = HUD)
		TSubclassOf<class UUserWidget> HUD;
	
	UPROPERTY()
		float BaseWalkSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Walk Speed")
		float SprintSpeed;
	
	UPROPERTY(EditDefaultsOnly, Category = Gun)
		TSubclassOf<AGun> Gunclass;

	UPROPERTY(EditDefaultsOnly, Category = Gun)
		TArray<AGun*> Weapons;

	

	UPROPERTY(EditDefaultsOnly, Category = Grenade)
		TSubclassOf<AGrenade> Grenadeclass;

	UFUNCTION(BlueprintCallable,Category = Grenade)
		void ThrowGrenade();

	bool FireModeChangeb;
	

	FTimerHandle TimerHandle;
	FTimerHandle SprintTimer;
	FTimerHandle PlayerDeathTimer;
	FTimerHandle AutomaticBurst;
	FTimerHandle GrenadeToss;
	UCharacterMovementComponent* MovmentPlayer;
	FTimeline RecoilTimeLine;
	int32 WeaponIndex;
	bool bIsReloading;
	void LookUp(float value);
	void Turn(float value);
	void MoveForward(float value);
	void MoveRight(float value);
	void StartFire();
	void StopFire();
	void StopBurst();
	void FireShot();
	void Sprint();
	void DestroyPlayer();
	void SwitchToNextPrimaryWeapon();
	void EquipItem();
	void Zoom();
	void StopZoom();
	void Reload();
	void OnStartReload();
	void ChangeFireMode();
	void GunFire();
	void HoldGreande();
	void GrenadeTossMontage();
	void ShowGun();

};
