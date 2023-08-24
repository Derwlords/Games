// Fill out your copyright notice in the Description page of Project Settings.


#include "Grenade.h"
#include "Components/SphereComponent.h"
// Sets default values
AGrenade::AGrenade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GrenadeMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Grenade Mesh"));
	GrenadeMesh->SetupAttachment(RootComponent);
	DamageSphere = CreateDefaultSubobject<USphereComponent>("DamageSphere");
	DamageSphere->SetupAttachment(GrenadeMesh);
	


}

// Called when the game starts or when spawned
void AGrenade::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrenade::Explode()
{
	GrenadeMesh->SetSimulatePhysics(false);
	DamageSphere->SetRelativeLocation(GrenadeMesh->GetRelativeLocation());
	
	

	TArray<AActor*> OverlapingActors;
	DamageSphere->GetOverlappingActors(OverlapingActors);
	for (AActor* Actor : OverlapingActors)
	{
		UE_LOG(LogTemp, Error, TEXT("Name Actor: %s"), *Actor->GetName());
		/*Actor->FindComponentByClass<UHealthComponent>()->DealDamage(GrenadeDamage);
		if (Actor->FindComponentByClass<UHealthComponent>()->IsDead())
		{
			Actor->Destroy();
		}*/
	}
	Destroy();
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

