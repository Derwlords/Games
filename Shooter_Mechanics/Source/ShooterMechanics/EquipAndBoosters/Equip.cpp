// Fill out your copyright notice in the Description page of Project Settings.


#include "Equip.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "ShooterMechanics/Player/ShooterPlayerClass.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
// Sets default values
AEquip::AEquip()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EquipTakeCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Take Zone"));
	EquipTakeCollision->SetupAttachment(RootComponent);
	
}


// Called when the game starts or when spawned
void AEquip::BeginPlay()
{
	EquipTakeCollision->OnComponentBeginOverlap.AddDynamic(this, &AEquip::OnHit);
	EquipTakeCollision->OnComponentEndOverlap.AddDynamic(this, &AEquip::Stop);
	ItemWidget = CreateWidget<UUserWidget>(GetWorld(), ItemEquipWidget);
	Super::BeginPlay();
}

// Called every frame
void AEquip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEquip::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	Player = Cast<AShooterPlayerClass>(OtherActor);
	if (Player)
	{
		Player->IsOverlappingItem = true;
		
		if (ItemWidget)
		{
			
			ItemWidget->AddToViewport();
			
		}
	}
}

void AEquip::Stop(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ItemWidget)
	{
		ItemWidget->RemoveFromViewport();
	}
	Player->IsOverlappingItem = false;
}


