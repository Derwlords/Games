// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerClass.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "ShooterMechanics/Weapons/Grenade.h"
#include "Components/PrimitiveComponent.h"
#include "ShooterMechanics/Components/HealthComponent.h"
#include "ShooterMechanics/Components/PlayerMovementComponent.h"
#include "ShooterMechanics/Components/WeaponComponent.h"
#include "ShooterMechanics/Components/GrenadeComponent.h"
// Sets default values
AShooterPlayerClass::AShooterPlayerClass()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	PlayerMovementComponent = CreateDefaultSubobject<UPlayerMovementComponent>(TEXT("MovementComponent"));
	PlayerMovementComponent->SetPlayerMovementComponent(GetCharacterMovement());

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));

	GrenadeComponent = CreateDefaultSubobject<UGrenadeComponent>(TEXT("GrenadeComponent"));
	

	WeaponIndex = 0;
	IsOverlappingItem = false;
	
}

// Called when the game starts or when spawned
void AShooterPlayerClass::BeginPlay()
{
	Player_HUD = CreateWidget(GetWorld(), HUD);

	Super::BeginPlay();

	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	
	
	if (Player_HUD)
	{
		Player_HUD->AddToViewport();
	}

}

// Called every frame
void AShooterPlayerClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	WeaponComponent->Recoil(DeltaTime);
	
}

// Called to bind functionality to input
void AShooterPlayerClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AShooterPlayerClass::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AShooterPlayerClass::StopFire);

	PlayerInputComponent->BindAction("Grenade Toss", IE_Pressed, this, &AShooterPlayerClass::HoldGrenade);
	PlayerInputComponent->BindAction("Grenade Toss", IE_Released, this, &AShooterPlayerClass::GrenadeToss);

	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &AShooterPlayerClass::Zoom);
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &AShooterPlayerClass::StopZoom);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed,this, &AShooterPlayerClass::Sprint);

	PlayerInputComponent->BindAction("SwitchPrimary", IE_Pressed, this, &AShooterPlayerClass::SwitchToNextPrimaryWeapon);

	PlayerInputComponent->BindAction("Equip", IE_Pressed, this, &AShooterPlayerClass::EquipItem);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AShooterPlayerClass::OnStartReload);

	PlayerInputComponent->BindAction("ChangeFireMode", IE_Pressed, this, &AShooterPlayerClass::ChangeFireMode);


	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterPlayerClass::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShooterPlayerClass::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &AShooterPlayerClass::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &AShooterPlayerClass::Turn);

}



void AShooterPlayerClass::LookUp(float value)
{
	AddControllerPitchInput(value * GetWorld()->GetDeltaSeconds() * LookUpRate);
}

void AShooterPlayerClass::Turn(float value)
{
	AddControllerYawInput(value * TurnRate * GetWorld()->GetDeltaSeconds());
}

void AShooterPlayerClass::MoveForward(float value)
{
	PlayerMovementComponent->MoveForward(value);
}

void AShooterPlayerClass::MoveRight(float value)
{
	PlayerMovementComponent->MoveRight(value);
}

void AShooterPlayerClass::StartFire()
{
	if (!WeaponComponent)
	{
		return;
	}
	WeaponComponent->StartFire();
}
void AShooterPlayerClass::StopFire()
{
	if (!WeaponComponent)
	{
		return;
	}
	WeaponComponent->StopFire();
}








void AShooterPlayerClass::SwitchToNextPrimaryWeapon()
{

	//switch (WeaponIndex)
	//{
	//	case 0:
	//		if (Weapons.Num() > 1)
	//		{
	//			WeaponIndex = 1;
	//			SwitchWeaponMesh(WeaponIndex);
	//		}
	//		else
	//		{
	//			WeaponIndex = 0;
	//			SwitchWeaponMesh(WeaponIndex);
	//		}
	//		break;
	//	case 1:
	//		if (Weapons.Num() > 2)
	//		{
	//			WeaponIndex = 2;
	//			SwitchWeaponMesh(WeaponIndex);
	//		}
	//		else
	//		{
	//			WeaponIndex = 0;
	//			SwitchWeaponMesh(WeaponIndex);
	//		}
	//		break;
	//	case 2:
	//		if (Weapons.Num() > 3)
	//		{
	//			WeaponIndex = 3;
	//			SwitchWeaponMesh(WeaponIndex);
	//		}
	//		else
	//		{
	//			WeaponIndex = 0;
	//			SwitchWeaponMesh(WeaponIndex);
	//		}
	//		break;
	//	default:
	//		break;

	//}
}

void AShooterPlayerClass::EquipItem()
{
	if (IsOverlappingItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("You pick up item"));
	}
}

void AShooterPlayerClass::Zoom()
{

	if (!WeaponComponent)
	{
		return;

	}
	WeaponComponent->Zoom();
}

void AShooterPlayerClass::StopZoom()
{
	if (!WeaponComponent)
	{
		return;

	}
	WeaponComponent->StopZoom();
}




void AShooterPlayerClass::HoldGrenade()
{
	if (!GrenadeComponent)
	{
		return;
	}
	GrenadeComponent->HoldGrenade();
}

void AShooterPlayerClass::GrenadeToss()
{
	if (!GrenadeComponent)
	{
		return;
	}
	GrenadeComponent->GrenadeToss();
}




void AShooterPlayerClass::Sprint()
{
	if (!PlayerMovementComponent)
	{
		return;
	}
	PlayerMovementComponent->Sprint();
}

void AShooterPlayerClass::OnStartReload()
{
	if(!WeaponComponent)
	{
		return;

	}
	WeaponComponent->OnStartReload();
}



void AShooterPlayerClass::ChangeFireMode()
{
	if (!WeaponComponent)
	{
		return;

	}

	WeaponComponent->ChangeFireMode();


}



void AShooterPlayerClass::Death()
{
	
}





float AShooterPlayerClass::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!HealthComponent)
	{
		return 0.f;
	}
	float DamageAplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageAplied = FMath::Min(HealthComponent->Health, DamageAplied);
	HealthComponent->Health -= DamageAplied;
	if (!HealthComponent->Health || HealthComponent->Health < 0)
	{
	GetWorldTimerManager().SetTimer(DeathTimer, this, &AShooterPlayerClass::DestroyCharacter, 1,false);
	}
	return DamageAplied;
}





