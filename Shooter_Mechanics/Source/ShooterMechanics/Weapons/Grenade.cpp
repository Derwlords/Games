// Fill out your copyright notice in the Description page of Project Settings.


#include "Grenade.h"
#include "Components/SphereComponent.h"
#include "ShooterMechanics/Components/HealthComponent.h"
// Sets default values
AGrenade::AGrenade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	

	GrenadeMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GrenadeMesh"));
	GrenadeMesh->SetupAttachment(RootComponent);
	DamageSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SpehereComponent"));
	DamageSphere->SetupAttachment(GrenadeMesh);
	
	FuseLenght = 5.f;
}

// Called when the game starts or when spawned
void AGrenade::BeginPlay()
{
	Super::BeginPlay();
	if (ThrowAnimation)
	{
		GrenadeMesh->PlayAnimation(ThrowAnimation, false);
	}
}

// Called every frame
void AGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AGrenade::OnReleased(FVector ForwardVector)
{
	ForwardVector *= GrenadeTossImpulse;
	GrenadeMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	GrenadeMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GrenadeMesh->SetSimulatePhysics(true);
	GrenadeMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
	GrenadeMesh->AddImpulse(ForwardVector);
	
	FTimerHandle TExplodeHandle;

	GetWorld()->GetTimerManager().SetTimer(TExplodeHandle, this, &AGrenade::Explode, FuseLenght);
}

void AGrenade::Explode()
{
	
	GrenadeMesh->SetSimulatePhysics(false);
	DamageSphere->SetWorldLocation(GrenadeMesh->GetComponentLocation());
	TArray<AActor*> OverlapingActors;
	DamageSphere->GetOverlappingActors(OverlapingActors);
	for (AActor* Actor : OverlapingActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("Name Actor: %s"), *Actor->GetName());
		Actor->FindComponentByClass<UHealthComponent>()->DealDamage(GrenadeDamage);
		if (Actor->FindComponentByClass<UHealthComponent>()->IsDead())
		{
			Actor->Destroy();
		}
	}
	Destroy();
}




