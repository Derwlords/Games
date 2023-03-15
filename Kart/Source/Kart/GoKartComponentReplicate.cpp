// Fill out your copyright notice in the Description page of Project Settings.


#include "GoKartComponentReplicate.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UGoKartComponentReplicate::UGoKartComponentReplicate()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
	// ...
}


// Called when the game starts
void UGoKartComponentReplicate::BeginPlay()
{
	Super::BeginPlay();
	SetIsReplicated(true);
	MovmentComponent = GetOwner()->FindComponentByClass<UGoKartMovmentComponent>();
	// ...
	
}


// Called every frame
void UGoKartComponentReplicate::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (MovmentComponent == nullptr) return;
	FGoKartMove LastMove = MovmentComponent->GetLastMove();
	if (GetOwnerRole() == ROLE_AutonomousProxy)
	{
		UnacknowledgeMoves.Add(LastMove);
		Server_SendMove(LastMove);
	}

	if (GetOwner()->GetRemoteRole() == ROLE_SimulatedProxy)
	{
		UpdateServerState(LastMove);
	}


	if (GetOwnerRole() == ROLE_SimulatedProxy)
	{
		MovmentComponent->SimulateMove(ServerState.LastMove);
	}



}

void UGoKartComponentReplicate::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UGoKartComponentReplicate, ServerState);


}

void UGoKartComponentReplicate::OnRep_ServerState()
{
	if (MovmentComponent == nullptr) return;

	GetOwner()->SetActorTransform(ServerState.Transform);
	MovmentComponent->SetVelocity(ServerState.Velocity);
	ClearAcknowledgMoves(ServerState.LastMove);
	for (const FGoKartMove& Move : UnacknowledgeMoves)
	{
		MovmentComponent->SimulateMove(Move);
	}
}
void UGoKartComponentReplicate::UpdateServerState(const FGoKartMove& Move)
{
	ServerState.LastMove = Move;
	ServerState.Transform = GetOwner()->GetActorTransform();
	ServerState.Velocity = MovmentComponent->GetVelocity();
}
void UGoKartComponentReplicate::Server_SendMove_Implementation(FGoKartMove Move)
{
	if (MovmentComponent == nullptr) return;

	MovmentComponent->SimulateMove(Move);
	UpdateServerState(Move);
}
bool UGoKartComponentReplicate::Server_SendMove_Validate(FGoKartMove Move)
{
	return true; //TODO: Make better validation
}

void UGoKartComponentReplicate::ClearAcknowledgMoves(FGoKartMove LastMove)
{
	TArray<FGoKartMove> NewMoves;

	for (const FGoKartMove& Move : UnacknowledgeMoves)
	{
		if (Move.Time > LastMove.Time)
		{
			NewMoves.Add(Move);
		}

	}
	UnacknowledgeMoves = NewMoves;
}



