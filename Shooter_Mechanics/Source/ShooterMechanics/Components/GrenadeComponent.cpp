// Fill out your copyright notice in the Description page of Project Settings.


#include "GrenadeComponent.h"
#include "GameFramework/Character.h"
#include "ShooterMechanics/Weapons/Grenade.h"
#include "Kismet/KismetMathLibrary.h"
#include "ShooterMechanics/Player/ShooterPlayerClass.h"
#include "ShooterMechanics/Components/WeaponComponent.h"
#include "ShooterMechanics/Weapons/Gun.h"
// Sets default values for this component's properties
UGrenadeComponent::UGrenadeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrenadeComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AShooterPlayerClass>(GetOwner());
	
}


// Called every frame
void UGrenadeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGrenadeComponent::HoldGrenade()
{
	if (!Grenadeclass || !GrenadeMontage)
	{
		return;
	}

	Grenade = GetWorld()->SpawnActor<AGrenade>(Grenadeclass);

	if (!Grenade)
	{
		return;
	}
	USkeletalMeshComponent* PlayerMesh = Cast<ACharacter>(GetOwner())->GetMesh();
	Grenade->AttachToComponent(PlayerMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("GrenadeSpawn"));


	if (UAnimInstance* AnimInstance = PlayerMesh->GetAnimInstance())
	{
		/*Gun->SetActorHiddenInGame(true);*/
		AnimInstance->Montage_Play(GrenadeMontage);

	}


	FTimerHandle GunHiden;
	GetWorld()->GetTimerManager().SetTimer(GunHiden, this, &UGrenadeComponent::ShowGun, 2);

}

void UGrenadeComponent::GrenadeToss()
{
	USkeletalMeshComponent* PlayerMesh = Cast<ACharacter>(GetOwner())->GetMesh();
	if (UAnimInstance* AnimInstance = PlayerMesh->GetAnimInstance())
	{
		if (!GrenadeMontage)
		{
			return;
		}

		Player->GetWeaponComponent()->GetGun()->SetActorHiddenInGame(true);
		AnimInstance->Montage_Play(TossGrenadeMontage);
		GetWorld()->GetTimerManager().SetTimer(GrenadeTossTimerHandle, this, &UGrenadeComponent::ThrowGrenade, 1.85f);


	}
}

void UGrenadeComponent::ThrowGrenade()
{
	if (!Grenade)
	{
		return;
	}

	Grenade->OnReleased(UKismetMathLibrary::GetForwardVector(Cast<APawn>(GetOwner())->GetControlRotation()));


}

void UGrenadeComponent::ShowGun()
{
	Player->GetWeaponComponent()->GetGun()->SetActorHiddenInGame(false);
}