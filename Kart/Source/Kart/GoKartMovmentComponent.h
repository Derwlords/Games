// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoKartMovmentComponent.generated.h"

USTRUCT()
struct FGoKartMove
{
	GENERATED_USTRUCT_BODY()


	UPROPERTY()
	float Throttle;
	UPROPERTY()
	float StreetingThrow;

	UPROPERTY()
	float DeltaTime;
	UPROPERTY()
	float Time;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KART_API UGoKartMovmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGoKartMovmentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SimulateMove(const FGoKartMove& Move);



	FVector GetVelocity() { return Velocity; };
	void SetVelocity(FVector Val) { Velocity = Val; };

	void SetThrottle(float Val) { Throttle = Val; };
	void SetSteeringThrow(float Val) { m_StreetingThrow = Val; };

	FGoKartMove GetLastMove() { return LastMove; }

private:


	FGoKartMove CreateMove(float DeltaTime);

	float Throttle;
	float m_StreetingThrow;

	

	FVector Velocity;

	
	void ApplyRotation(float DeltaTime, float StreetingThrow);
	void UpdateLocationFromVector(float DeltaTime);

	FVector GetResistence();
	FVector GetRollingResistence();

	//The mass of rhe car
	UPROPERTY(EditDefaultsOnly, Category = "Car Mass")
		float Mass = 1000.f;

	//The force applied to the car when the throttle is fully down (N)
	UPROPERTY(EditDefaultsOnly, Category = "Car Mass")
		float MaxDrivingForce = 10000.f;

	//The number of degrees per second at full control throw (degrees/s)
	UPROPERTY(EditDefaultsOnly, Category = "Car Mass")
		float MaxDegreesPerSecond = 90.f;

	UPROPERTY(EditAnywhere)
		float DragCoefficient = 16.f;

	UPROPERTY(EditAnywhere)
		float RollingResistenceCoefficient = 0.015f;

	UPROPERTY(EditAnywhere, Category = "Car Mass")
		float MinTurnRadius = 10.f;

	FGoKartMove LastMove;
		
};
