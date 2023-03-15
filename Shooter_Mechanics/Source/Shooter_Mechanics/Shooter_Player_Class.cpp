// Fill out your copyright notice in the Description page of Project Settings.


#include "Shooter_Player_Class.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Gun.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "Grenade.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "HealthComponent.h"
// Sets default values
AShooter_Player_Class::AShooter_Player_Class()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	HealthComponent = CreateAbstractDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	WeaponIndex = 0;
	IsOverlappingItem = false;
	FireModeChangeb = true;
}

// Called when the game starts or when spawned
void AShooter_Player_Class::BeginPlay()
{

	Gun = GetWorld()->SpawnActor<AGun>(Gunclass);
	Gun->SetOwner(this);
	Player_HUD = CreateWidget(GetWorld(), HUD);
	Super::BeginPlay();

	MovmentPlayer = GetCharacterMovement();
	if (!MovmentPlayer) return;
	BaseWalkSpeed = MovmentPlayer->MaxWalkSpeed;

	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("Rifle_Hand"));
	if (!Gun) return;


	if (Player_HUD)
	{
		Player_HUD->AddToViewport();
	}
	
	FOnTimelineFloat XRecoilCurve;
	FOnTimelineFloat YRecoilCurve;

	XRecoilCurve.BindUFunction(this, FName("StartHorizontalRecoil"));
	YRecoilCurve.BindUFunction(this, FName("StartVerticalRecoil"));


	if (!HorizontalCurve || !VerticalCurve) return;

	RecoilTimeLine.AddInterpFloat(HorizontalCurve, XRecoilCurve);
	RecoilTimeLine.AddInterpFloat(VerticalCurve, YRecoilCurve);


	bIsReloading = false;
}

// Called every frame
void AShooter_Player_Class::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (RecoilTimeLine.IsPlaying())
	{

	RecoilTimeLine.TickTimeline(DeltaTime);
	}

	if (RecoilTimeLine.IsReversing())
	{
		RecoilTimeLine.TickTimeline(DeltaTime);
	}
}

// Called to bind functionality to input
void AShooter_Player_Class::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AShooter_Player_Class::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AShooter_Player_Class::StopFire);

	PlayerInputComponent->BindAction("Grenade Toss", IE_Pressed, this, &AShooter_Player_Class::HoldGreande);
	PlayerInputComponent->BindAction("Grenade Toss", IE_Released, this, &AShooter_Player_Class::GrenadeTossMontage);

	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &AShooter_Player_Class::Zoom);
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &AShooter_Player_Class::StopZoom);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AShooter_Player_Class::Sprint);

	PlayerInputComponent->BindAction("SwitchPrimary", IE_Pressed, this, &AShooter_Player_Class::SwitchToNextPrimaryWeapon);

	PlayerInputComponent->BindAction("Equip", IE_Pressed, this, &AShooter_Player_Class::EquipItem);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AShooter_Player_Class::OnStartReload);

	PlayerInputComponent->BindAction("ChangeFireMode", IE_Pressed, this, &AShooter_Player_Class::ChangeFireMode);


	PlayerInputComponent->BindAxis("MoveForward", this, &AShooter_Player_Class::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShooter_Player_Class::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &AShooter_Player_Class::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &AShooter_Player_Class::Turn);

}



void AShooter_Player_Class::LookUp(float value)
{
	AddControllerPitchInput(value * GetWorld()->GetDeltaSeconds() * LookUpRate);
}

void AShooter_Player_Class::Turn(float value)
{
	AddControllerYawInput(value * TurnRate * GetWorld()->GetDeltaSeconds());
}

void AShooter_Player_Class::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector(), value);
}

void AShooter_Player_Class::MoveRight(float value)
{
	AddMovementInput(GetActorRightVector(), value);
}

void AShooter_Player_Class::StartFire()
{
	GunFire();
	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AShooter_Player_Class::GunFire, TimeBetwenShoots, true);
}
void AShooter_Player_Class::StopFire()
{
	EndRecoil();
	GetWorldTimerManager().ClearTimer(TimerHandle);
}

void AShooter_Player_Class::StopBurst()
{
	EndRecoil();
	GetWorldTimerManager().ClearTimer(AutomaticBurst);
}

void AShooter_Player_Class::FireShot()
{
	
		if (FMath::Clamp(Gun->ClipAmmo, 0, Gun->MaxClipAmmo) && bIsReloading == false)
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


void AShooter_Player_Class::Sprint()
{
	if (MovmentPlayer->MaxWalkSpeed == BaseWalkSpeed)
	{
		MovmentPlayer->MaxWalkSpeed = SprintSpeed;
	}
	else
	{
		MovmentPlayer->MaxWalkSpeed = BaseWalkSpeed;
	
	}
}

void AShooter_Player_Class::DestroyPlayer()
{
	Destroy();
}

void AShooter_Player_Class::SwitchToNextPrimaryWeapon()
{

	switch (WeaponIndex)
	{
		case 0:
			if (Weapons.Num() > 1)
			{
				WeaponIndex = 1;
				SwitchWeaponMesh(WeaponIndex);
			}
			else
			{
				WeaponIndex = 0;
				SwitchWeaponMesh(WeaponIndex);
			}
			break;
		case 1:
			if (Weapons.Num() > 2)
			{
				WeaponIndex = 2;
				SwitchWeaponMesh(WeaponIndex);
			}
			else
			{
				WeaponIndex = 0;
				SwitchWeaponMesh(WeaponIndex);
			}
			break;
		case 2:
			if (Weapons.Num() > 3)
			{
				WeaponIndex = 3;
				SwitchWeaponMesh(WeaponIndex);
			}
			else
			{
				WeaponIndex = 0;
				SwitchWeaponMesh(WeaponIndex);
			}
			break;
		default:
			break;

	}
}

void AShooter_Player_Class::EquipItem()
{
	if (IsOverlappingItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("You pick up item"));
	}
}

void AShooter_Player_Class::Zoom()
{

	if (SpringArm )
	{
		SpringArm->TargetArmLength = 150.f;
		

		if (auto CharacterMovment = GetCharacterMovement())
		{
			CharacterMovment->MaxWalkSpeed = 300.f;
		}

		if (bIsReloading)
		{
			StopZoom();
		}
	}
}

void AShooter_Player_Class::StopZoom()
{
	if (SpringArm)
	{
		SpringArm->TargetArmLength = 450;
		

		if (auto CharacterMovment = GetCharacterMovement())
		{
			CharacterMovment->MaxWalkSpeed = BaseWalkSpeed;
		}
	}
}
void AShooter_Player_Class::GrenadeTossMontage()
{
	USkeletalMeshComponent* PlayerMesh = GetMesh();
	if (UAnimInstance* AnimInstance = PlayerMesh->GetAnimInstance())
	{
		if (GrenadeMontage)
		{
			Gun->SetActorHiddenInGame(true);
			AnimInstance->Montage_Play(TossGrenadeMontage);
			GetWorld()->GetTimerManager().SetTimer(GrenadeToss, this, &AShooter_Player_Class::ThrowGrenade, 1.85f);

		}
	}
}
void AShooter_Player_Class::ThrowGrenade()
{
	if (Grenade)
	{

	
		Grenade->OnReleased(UKismetMathLibrary::GetForwardVector(GetControlRotation()));



	}
}

void AShooter_Player_Class::HoldGreande()
{
	if (Grenadeclass)
	{
		Grenade = GetWorld()->SpawnActor<AGrenade>(Grenadeclass);
		if (Grenade)
		{
			USkeletalMeshComponent* PlayerMesh = GetMesh();
			Grenade->AttachToComponent(PlayerMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("GrenadeSpawn"));
			if (UAnimInstance* AnimInstance = PlayerMesh->GetAnimInstance())
			{
				if (GrenadeMontage)
				{
					Gun->SetActorHiddenInGame(true);
					AnimInstance->Montage_Play(GrenadeMontage);

				}
			}
		}
	}
	FTimerHandle GunHiden;
	GetWorld()->GetTimerManager().SetTimer(GunHiden, this, &AShooter_Player_Class::ShowGun, 2);
	
}


void AShooter_Player_Class::ShowGun()
{
	Gun->SetActorHiddenInGame(false);
}

void AShooter_Player_Class::OnStartReload()
{
	FTimerHandle ReloadHandle;
	if (Gun->ClipAmmo < Gun->MaxClipAmmo && Gun->TotalAmmo > 0)
	{
		IsReloading = true;
	}
	if (bIsReloading) return;
	bIsReloading = true;
	GetWorld()->GetTimerManager().SetTimer(ReloadHandle, this, &AShooter_Player_Class::Reload, Gun->ReloadTime);
}

void AShooter_Player_Class::ChangeFireMode()
{
	if (FireModeChangeb)
	{
		FireModeChangeb = false;
	}
	else
	{
		FireModeChangeb = true;


	}


}

void AShooter_Player_Class::GunFire()
{
	if (FireModeChangeb)
	{
		FireShot();
	}
	else
	{
		
	FireShot();
	GetWorld()->GetTimerManager().SetTimer(AutomaticBurst, this, &AShooter_Player_Class::FireShot, 0.2,true);
	FTimerHandle StopBurst;
	GetWorld()->GetTimerManager().SetTimer(StopBurst, this, &AShooter_Player_Class::StopBurst, 1);
	}
	
	
}

void AShooter_Player_Class::PlayerDead()
{
	if (HealthComponent->IsDead())
	{
		GetWorldTimerManager().SetTimer(PlayerDeathTimer, this, &AShooter_Player_Class::DestroyPlayer, 1, false);
	}
}



void AShooter_Player_Class::Reload()
{
	 
	
	if (FMath::Clamp(Gun->TotalAmmo,0, Gun->MaxTotalAmmo ))
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
	
	IsReloading = false;
	bIsReloading = false;
}

float AShooter_Player_Class::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageAplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageAplied = FMath::Min(Health, DamageAplied);
	Health -= DamageAplied;
	if (!Health || Health < 0)
	{
	GetWorldTimerManager().SetTimer(PlayerDeathTimer, this, &AShooter_Player_Class::DestroyPlayer, 1,false);
	}
	return DamageAplied;
}



void AShooter_Player_Class::StartHorizontalRecoil(float value)
{
	AddControllerYawInput(value);
}

void AShooter_Player_Class::StartVerticalRecoil(float value)
{
	AddControllerPitchInput(value);
}

void AShooter_Player_Class::StartRecoil()
{
	RecoilTimeLine.PlayFromStart();
}

void AShooter_Player_Class::EndRecoil()
{
	RecoilTimeLine.Stop();
}