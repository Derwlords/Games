// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "Shooter/Weapon/AK47.h"
#include"Shooter/BaseCharacter/BaseCharacter.h"
#include "Shooter/Weapon/Grenade.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SphereComponent.h"
// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Player = Cast<ABaseCharacter>(GetOwner());
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	
	FirstWeapon = GetWorld()->SpawnActor<AAK47>(FirstWeaponClass);
	if (!FirstWeapon) { return; }
	FirstWeapon->SetOwner(Player);

	Super::BeginPlay();

	

	FirstWeapon->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("WeaponSlot"));

	if (!FirstWeapon) { return; }
	
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponComponent::HoldGrenade()
{
	if (!GrenadeClass) { return; }

		Grenade = GetWorld()->SpawnActor<AGrenade>(GrenadeClass);

	if (!Grenade) { return; }
		
	Grenade->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(TEXT("WeaponSlot")));

	if (UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance())
	{ 
		if (!TossGrenadeMontage) { return; }
		FirstWeapon->SetActorHiddenInGame(true);
		AnimInstance->Montage_Play(TossGrenadeMontage);
		GetWorld()->GetTimerManager().SetTimer(GrenadeToss, this, &UWeaponComponent::ThrowGrenade, ThrowDelay);
	}
				


}

void UWeaponComponent::ThrowGrenade()
{
	if (!Grenade) { return; }
	Grenade->OnReleased(UKismetMathLibrary::GetForwardVector(Player->GetControlRotation()));

	
	GetWorld()->GetTimerManager().SetTimer(ShowFirstWeapon, this,&UWeaponComponent::ShowWeapon, ShowWeaponDelay);
	
}

void UWeaponComponent::ShowWeapon()
{
	FirstWeapon->SetActorHiddenInGame(false);
}

