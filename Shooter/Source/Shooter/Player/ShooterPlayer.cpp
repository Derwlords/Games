// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Shooter/Component/WeaponComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Shooter/Enemy/Enemy.h"
#include "Math/Vector.h"
// Sets default values
AShooterPlayer::AShooterPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraBoom"));
	Camera->SetupAttachment(SpringArm);


	bClimbing = false;
}
void AShooterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bClimbing)
	{
		StartClimbing();
	}
	
}

void AShooterPlayer::BeginPlay()
{
	

	Super::BeginPlay();

	Capsule = GetCapsuleComponent();
	if (!Capsule)
	{
		return;
	}

	
}




void AShooterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	 
	PlayerInputComponent->BindAction("StopClimbing", IE_Pressed, this, &AShooterPlayer::StopClimbing);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ABaseCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ABaseCharacter::StopSprint);

	

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AShooterPlayer::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AShooterPlayer::StopJumping);
	

	PlayerInputComponent->BindAction("TakeAim", IE_Pressed, this, &AShooterPlayer::StartTakeAim);
	PlayerInputComponent->BindAction("TakeAim", IE_Released, this, &AShooterPlayer::StopTakeAim);

	PlayerInputComponent->BindAction("ThrowGrenade", IE_Pressed, this, &AShooterPlayer::GrenadeThrow);

	PlayerInputComponent->BindAxis("LookUp", this, &AShooterPlayer::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &AShooterPlayer::Turn);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShooterPlayer::MoveRight);
}

void AShooterPlayer::MoveForward(float value)
{
	if (bClimbing)
	{
		value *= ClimbingSpeed;
		AddMovementInput(GetActorUpVector(), value);

	}
	else
	{
		
			Super::MoveForward(value);
		
		
	}
}

void AShooterPlayer::MoveRight(float value)
{
	if (bClimbing)
	{
		value *= ClimbingSpeed;
		AddMovementInput(GetActorRightVector(), value);

	}
	else
	{
		Super::MoveRight(value);
	}
}

void AShooterPlayer::Turn(float value)
{
	AddControllerYawInput(value * GetWorld()->GetDeltaSeconds() * LookUpRate);
}

void AShooterPlayer::LookUp(float value)
{
	AddControllerPitchInput(value * GetWorld()->GetDeltaSeconds() * TurnRate);
}

void AShooterPlayer::StartTakeAim()
{
	CharacterMovment->MaxWalkSpeed = TakeAimSpeed;
}

void AShooterPlayer::StopTakeAim()
{
	CharacterMovment->MaxWalkSpeed = BaseWalkSpeed;
}

void AShooterPlayer::GrenadeThrow()
{
	WeaponComponent->HoldGrenade();
}

void AShooterPlayer::Jump()
{
	Super::Jump();
	
}

void AShooterPlayer::StopJumping()
{
	Super::StopJumping();
}



void AShooterPlayer::StartClimbing()
{

	
	
	FHitResult HitResult;
	if (ClimbingTrace(HitResult) && bClimbing == false)
	{
		
		
		bClimbing = true;
		CharacterMovment->SetMovementMode(MOVE_Flying);
		CharacterMovment->StopMovementImmediately();
		
		 
		FRotator NewRotation = GetActorRotation();
		
		
		HitResult.ImpactPoint.Z -= 50.f;
		FVector NewLocation = (HitResult.ImpactPoint) + (HitResult.Normal * 60.f);
		
		Capsule->SetWorldTransform(FTransform(NewRotation , NewLocation, FVector(1,1,1)));
		bUseControllerRotationYaw = false;
	}
	
}
bool AShooterPlayer::ClimbingTrace(FHitResult& HitResult)
{
	USkeletalMeshComponent* PlayerMesh = GetMesh();
	if (!PlayerMesh)
	{
		return false;
	}

	FVector LineStart = PlayerMesh->GetBoneLocation(TEXT("Neck"));
	FVector LineEnd = (GetActorForwardVector() * 40.f) + LineStart;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	
	DrawDebugLine(GetWorld(), LineStart, LineEnd, FColor::Red, false);
	return GetWorld()->LineTraceSingleByChannel(HitResult, LineStart, LineEnd, ECollisionChannel::ECC_Pawn, Params);
}

void AShooterPlayer::StopClimbing()
{
	CharacterMovment->SetMovementMode(MOVE_Falling);
	bClimbing = false;
	bUseControllerRotationYaw = true;
	CharacterMovment->MaxWalkSpeed = BaseWalkSpeed;
}
