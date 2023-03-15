// Fill out your copyright notice in the Description page of Project Settings.


#include "GoKart.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"


// Sets default values
AGoKart::AGoKart()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	MovmentComponent = CreateDefaultSubobject<UGoKartMovmentComponent>(TEXT("MovmentComponent"));
	ReplicateComponent = CreateDefaultSubobject<UGoKartComponentReplicate>(TEXT("REplicateComponent"));
}

// Called when the game starts or when spawned
void AGoKart::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		NetUpdateFrequency = 1;
	}
}

FString GetEnumText(ENetRole Role)
{
	switch (Role)
	{
	case ROLE_None:
		return "None";
		break;
	case ROLE_AutonomousProxy:
		return "AutonomousProx";
		break;
	case ROLE_SimulatedProxy:
		return "SimulatedProxy";
		break;
	case ROLE_Authority:
		return "Authority";
		break;
	default:
		return "ERROR";
		break;

	}
}

// Called every frame
void AGoKart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	
	
	
	
	
	DrawDebugString(GetWorld(), FVector(0, 0, 100), GetEnumText(AActor::GetLocalRole()), this, FColor::White, DeltaTime);
}




void AGoKart::MoveForward(float Value)
{
	if (MovmentComponent == nullptr) return;
	MovmentComponent->SetThrottle(Value);

}

void AGoKart::MoveRight(float Value)
{
	if (MovmentComponent == nullptr) return;
	MovmentComponent->SetSteeringThrow(Value);
	
}



// Called to bind functionality to input
void AGoKart::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGoKart::MoveForward);
	PlayerInputComponent->BindAxis("TurnRight", this, &AGoKart::MoveRight);

	PlayerInputComponent->BindAxis("LookUp");
	PlayerInputComponent->BindAxis("LookRight");


}




