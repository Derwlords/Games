// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/HUD.h"
#include "KartHud.generated.h"


UCLASS(config = Game)
class AKartHud : public AHUD
{
	GENERATED_BODY()

public:
	AKartHud();

	/** Font used to render the vehicle info */
	UPROPERTY()
	UFont* HUDFont;

	// Begin AHUD interface
	virtual void DrawHUD() override;
	// End AHUD interface
};
