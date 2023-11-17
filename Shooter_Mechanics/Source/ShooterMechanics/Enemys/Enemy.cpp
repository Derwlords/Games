// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/BoxComponent.h"
#include "ShooterMechanics/Player/ShooterPlayerClass.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "CollisionQueryParams.h"
#include "ShooterMechanics/Components/HealthComponent.h"
// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Collision"));
	DamageCollision->SetupAttachment(RootComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	DamageCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnHit);
	
	HealthComponent->Health = HealthComponent->GetMaxHealth();
	
	
	DamageCollision->OnComponentEndOverlap.AddDynamic(this, &AEnemy::ClearTimer);

	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	

	
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageAplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageAplied = FMath::Min(HealthComponent->Health, DamageAplied);
	HealthComponent->Health -= DamageAplied;
	EnemyIsDead();
	return DamageAplied;
}

void AEnemy::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{ 
	
	FCollisionQueryParams ColParams = FCollisionQueryParams(FName("Tsirla"), false, GetOwner());
	ColParams.AddIgnoredActor(GetOwner());
	ColParams.AddIgnoredActor(this);
	Player = Cast<AShooterPlayerClass>(OtherActor);
	if (Player)
	{
	
		EnemyIsDead();
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemy::ApplyDamage, 0.5, true, 0.1);
		
	}
	
	
}
void AEnemy::ClearTimer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}



void AEnemy::ApplyDamage()
{
	if (Player)
	{
		Player->HealthComponent->DealDamage(DamageValue);
	/*	Player->PlayerDead();*/
	}
}

bool AEnemy::PlayerInDamageCollision()
{

	if (DamageCollision->IsOverlappingActor(Player))
	{
		return true;
	}
	return false;
}

void AEnemy::DestroyEnemy()
{
	Destroy();
}

void AEnemy::EnemyIsDead()
{
	if (HealthComponent->IsDead())
	{
			DamageCollision->DestroyPhysicsState();
			DamageCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			APawn::DetachFromControllerPendingDestroy();
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetWorld()->GetTimerManager().SetTimer(EnemyDeathTimer, this, &AEnemy::DestroyEnemy, 2.2);
	}
}



