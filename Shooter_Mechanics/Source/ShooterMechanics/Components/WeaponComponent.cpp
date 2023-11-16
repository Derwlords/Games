// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ShooterMechanics/Player/ShooterPlayerClass.h"
#include "ShooterMechanics/Components/PlayerMovementComponent.h"
#include "ShooterMechanics/Weapons/Gun.h"
#include "GameFramework/Controller.h"
// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Player = Cast<AShooterPlayerClass>(GetOwner());

	bIsReloading = false;
	bFireModeChanged = true;

	SpeedInZoom = 300.f;

	if (!HorizontalCurve || !VerticalCurve) return;

	RecoilTimeLine.AddInterpFloat(HorizontalCurve, XRecoilCurve);
	RecoilTimeLine.AddInterpFloat(VerticalCurve, YRecoilCurve);


	
	
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Gun = GetWorld()->SpawnActor<AGun>(Gunclass);
	Gun->SetOwner(GetOwner());
	Super::BeginPlay();

	PlayerMovementComponent = Player->GetPLayerMovementComponent();

	Gun->AttachToComponent(Cast<ACharacter>(GetOwner())->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("Rifle_Hand"));
	

	

	XRecoilCurve.BindUFunction(this, FName("StartHorizontalRecoil"));
	YRecoilCurve.BindUFunction(this, FName("StartVerticalRecoil"));
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
void UWeaponComponent::Zoom()
{
	if (!Player)
	{
		return;
	}
	USpringArmComponent* SpringArm = Player->GetSpringArmComponent();
	if (SpringArm)
	{
		SpringArm->TargetArmLength = 150.f;


		if (PlayerMovementComponent)
		{
			PlayerMovementComponent->SetPlayerSpeed(SpeedInZoom);
		}

		if (bIsReloading)
		{
			StopZoom();
		}
	}
}
void UWeaponComponent::StopZoom()
{

	if (!Player)
	{
		return;
	}
	
	USpringArmComponent* SpringArm = Player->GetSpringArmComponent();
	if (SpringArm)
	{
		SpringArm->TargetArmLength = 450;

		

		PlayerMovementComponent->BaseWalk();

	}
}

void UWeaponComponent::StartFire()
{
	GunFire();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UWeaponComponent::GunFire, TimeBetwenShoots, true);
}

void UWeaponComponent::StopFire()
{
	EndRecoil();
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void UWeaponComponent::ChangeFireMode()
{
	if (bFireModeChanged)
	{
		bFireModeChanged = false;
	}
	else
	{
		bFireModeChanged = true;


	}
}

void UWeaponComponent::GunFire()
{
	if (bFireModeChanged)
	{
		FireShot();
	}
	else
	{

		FireShot();
		GetWorld()->GetTimerManager().SetTimer(AutomaticBurst, this, &UWeaponComponent::FireShot, 0.2, true);
		FTimerHandle StopBurst;
		GetWorld()->GetTimerManager().SetTimer(StopBurst, this, &UWeaponComponent::StopBurst, 1);
	}
}

void UWeaponComponent::StopBurst()
{
	
	EndRecoil();
	GetWorld()->GetTimerManager().ClearTimer(AutomaticBurst);
}

void UWeaponComponent::FireShot()
{
	if (FMath::Clamp(Gun->ClipAmmo, 0,Gun->MaxClipAmmo) && bIsReloading == false)
	{
		Gun->ClipAmmo -= 1;
		Gun->PullTriger();
		StartRecoil();
	}
	else
	{
		EndRecoil();
		OnStartReload();
	}
}

void UWeaponComponent::Recoil(float DeltaTime)
{
	if (RecoilTimeLine.IsPlaying())
	{

		RecoilTimeLine.TickTimeline(DeltaTime);
	}

	if (RecoilTimeLine.IsReversing())
	{
		RecoilTimeLine.TickTimeline(DeltaTime);
	}
}


void UWeaponComponent::StartRecoil()
{
	RecoilTimeLine.PlayFromStart();
}

void UWeaponComponent::EndRecoil()
{
	RecoilTimeLine.Stop();
}

void UWeaponComponent::OnStartReload()
{
	
	if (Gun->ClipAmmo < Gun->MaxClipAmmo && Gun->TotalAmmo > 0 && bIsReloading == false)
	{
		bIsReloading = true;
		FTimerHandle ReloadHandle;
		GetWorld()->GetTimerManager().SetTimer(ReloadHandle, this, &UWeaponComponent::Reload, Gun->ReloadTime);
		
	}
	

	
}


void UWeaponComponent::Reload()
{


	if (FMath::Clamp(Gun->TotalAmmo, 0, Gun->MaxTotalAmmo))
	{

		int32 AmmoNeedForReload = Gun->MaxClipAmmo - Gun->ClipAmmo;
		if (Gun->TotalAmmo >= AmmoNeedForReload)
		{
			Gun->ClipAmmo += AmmoNeedForReload;
			Gun->TotalAmmo -= AmmoNeedForReload;
		}
		else
		{
			Gun->ClipAmmo += Gun->TotalAmmo;
			Gun->TotalAmmo = 0;
		}

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("You don't have more ammo"));
	}

	bIsReloading = false;
	
}
