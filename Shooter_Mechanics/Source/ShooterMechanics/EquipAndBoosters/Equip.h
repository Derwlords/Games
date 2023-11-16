// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Equip.generated.h"

UCLASS()
class SHOOTERMECHANICS_API  AEquip : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEquip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
	UFUNCTION()
		void Stop(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
		UUserWidget* ItemWidget;

private:

	UPROPERTY(EditAnywhere)
	class UBoxComponent* EquipTakeCollision;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> ItemEquipWidget;
	class AShooterPlayerClass* Player;



};
