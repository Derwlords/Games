// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoKartMovmentComponent.h"
#include "GoKartComponentReplicate.generated.h"

USTRUCT()
struct FGoKartState
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY()
		FGoKartMove LastMove;

	UPROPERTY()
		FTransform Transform;

	UPROPERTY()
		FVector Velocity;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KART_API UGoKartComponentReplicate : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGoKartComponentReplicate();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	void ClearAcknowledgMoves(FGoKartMove LastMove);


	UFUNCTION(Server, Reliable, WithValidation)
		void Server_SendMove(FGoKartMove Move);

	UFUNCTION()
		void OnRep_ServerState();

	UPROPERTY(ReplicatedUsing = OnRep_ServerState)
		FGoKartState ServerState;

	TArray<FGoKartMove> UnacknowledgeMoves;

	UPROPERTY()
		UGoKartMovmentComponent* MovmentComponent;

	void UpdateServerState(const FGoKartMove& Move);
};
