// Copyright Epic Games, Inc. All Rights Reserved.

#include "KartGameMode.h"
#include "KartPawn.h"
#include "KartHud.h"

AKartGameMode::AKartGameMode()
{
	DefaultPawnClass = AKartPawn::StaticClass();
	HUDClass = AKartHud::StaticClass();
}
