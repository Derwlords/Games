// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DecalActor.h"
#include "Components/DecalComponent.h"
#include "Grenade.h"
// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(Mesh);

	MaxTotalAmmo = 300;
	MaxClipAmmo = 30;
	ClipAmmo = MaxClipAmmo;
	TotalAmmo = 90;
	ReloadTime = 4.f;
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTriger()
{

	FVector ShotDirection;
	FHitResult HitResult;
	if (GunTrace(HitResult, ShotDirection))
	{
		AActor* HitActor = HitResult.GetActor();

		if (HitActor)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, HitResult.Location, ShotDirection.Rotation());
			FPointDamageEvent DamageEvent = FPointDamageEvent(Damage, HitResult, ShotDirection, nullptr);
			AController* Controller = OwnerController();
			HitActor->TakeDamage(Damage, DamageEvent, Controller, this);
			
		}
		
		Decal = GetWorld()->SpawnActor<ADecalActor>(HitResult.Location,FRotator());
		if (Decal)
		{
			
			Decal->SetDecalMaterial(ShootDecalToSpawn);
			Decal->SetLifeSpan(5.f);
			Decal->GetDecal()->DecalSize = FVector(40.f, 32.f, 35.f);
			

		}
	}

	
}



bool AGun::GunTrace(FHitResult& HitResult, FVector& ShotDirection)
{
	AController* Controller = OwnerController();
	if (!Controller)return false;

	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;
	Controller->GetPlayerViewPoint(PlayerViewLocation, PlayerViewRotation);

	FVector End = PlayerViewLocation + PlayerViewRotation.Vector() * MaxRange;

	ShotDirection = -PlayerViewRotation.Vector();

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	Params.AddIgnoredActor(Grenade);
	
	
	return GetWorld()->LineTraceSingleByChannel(HitResult, PlayerViewLocation, End, ECollisionChannel::ECC_GameTraceChannel1, Params);


}

AController* AGun::OwnerController() const
{
	APawn* Controller = Cast<APawn>(GetOwner());
	if (!Controller) return nullptr;

	return Controller->GetController();
	
}



