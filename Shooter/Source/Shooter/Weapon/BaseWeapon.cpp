// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectyleSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(WeaponMesh);
	ProjectileSpawnPoint->SetRelativeLocation(FVector(64.f,0.f,8.f));
	MaxRange = 1000.f;
	Damage = 10.f;
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	InClip = MaxInClip;

}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseWeapon::PullTriger()
{
	FVector ShotDirection;
	FHitResult HitResult;
	if (GunTrace(HitResult, ShotDirection))
	{

		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			FPointDamageEvent DamageEvent = FPointDamageEvent(Damage, HitResult, ShotDirection, nullptr);
			AController* OwnerController = GetOwnerController();
			if (OwnerController)
			{
				return;
			}
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
}

bool ABaseWeapon::GunTrace(FHitResult& HitResult, FVector& ShotDicretion)
{
	AController* OwnerController = GetOwnerController();
	if (!OwnerController)
	{
		return false;
	}
	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;
	OwnerController->GetPlayerViewPoint(PlayerViewLocation, PlayerViewRotation);

	FVector End = PlayerViewLocation + PlayerViewRotation.Vector() * MaxRange;

	ShotDicretion = -PlayerViewRotation.Vector();
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(HitResult, PlayerViewLocation, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController* ABaseWeapon::GetOwnerController()
{
	APawn* pOwner = Cast<APawn>(GetOwner());
	if (!pOwner)
	{
		return nullptr;
	}

	return pOwner->GetController();
}


