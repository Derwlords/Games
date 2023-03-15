// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Enemy.h"
#include "Shooter_Player_Class.h"
#include "Engine/DecalActor.h"
#include "Components/DecalComponent.h"
#include "HealthComponent.h"
// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionSphare = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = CollisionSphare;

	ProjectileMevement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
	ProjectileMevement->UpdatedComponent = CollisionSphare;
	ProjectileMevement->InitialSpeed = 3000.f;
	ProjectileMevement->MaxSpeed = 3000.f;
	ProjectileMevement->bRotationFollowsVelocity = true;
	ProjectileMevement->bShouldBounce = true;

	
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionSphare->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnHit);

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	AShooter_Player_Class* Player = Cast<AShooter_Player_Class>(OtherActor);
	
	//if (Enemy)
	//{
	//	
	//	Enemy->DealDamage(damage);
	//	Destroy();
	//}

	//if (Player)
	//{
	//	Player->HealthComponent->DealDamage(damage);
	//	Destroy();
	//}
	Decal = GetWorld()->SpawnActor<ADecalActor>();
	if (Decal)
	{
		Decal->SetDecalMaterial(ShootDecalToSpawn);
		Decal->SetLifeSpan(5.f);
		Decal->GetDecal()->DecalSize = FVector(40.f, 32.f, 35.f);

	}
}

