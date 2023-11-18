// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "WeaponComponent.generated.h"

class AShooterPlayerClass;
class AGun;
class UPlayerMovementComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERMECHANICS_API  UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Recoil")
	class UCurveFloat* VerticalCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Recoil")
	class UCurveFloat* HorizontalCurve;

	UFUNCTION()
	void StartHorizontalRecoil(float value);
	UFUNCTION()
	void StartVerticalRecoil(float value);

	void StartRecoil();

	void EndRecoil();

	void Recoil(float DeltaTime);


	void Zoom();
	void StopZoom();
	
	void StartFire();
	void StopFire();

	void ChangeFireMode();
	
	void OnStartReload();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Reload)
	bool bIsReloading;

	UFUNCTION(BlueprintCallable)
	AGun* GetGun() { return Gun; }
private:
	AShooterPlayerClass* Player;

	UPlayerMovementComponent* PlayerMovementComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Speed")
	float SpeedInZoom;

	UPROPERTY(EditDefaultsOnly, Category = "Shoot")
	float TimeBetwenShoots;

	bool bFireModeChanged;


	void GunFire();
	void FireShot();
	void StopBurst();

	UPROPERTY(EditDefaultsOnly, Category = "Shoot")
	bool BurstShoots;


	FTimerHandle TimerHandle;
	FTimerHandle AutomaticBurst;

	void Reload();


	UPROPERTY(EditDefaultsOnly, Category = Gun)
	TSubclassOf<AGun> Gunclass;

	UPROPERTY(VisibleDefaultsOnly, Category = Gun)
	AGun* Gun;

	FTimeline RecoilTimeLine;

	FOnTimelineFloat XRecoilCurve;
	FOnTimelineFloat YRecoilCurve;
};
