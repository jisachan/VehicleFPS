// Copyright Epic Games, Inc. All Rights Reserved.

#include "VehicleFPSGameMode.h"
#include "VehicleFPSCharacter.h"
#include "UObject/ConstructorHelpers.h"

AVehicleFPSGameMode::AVehicleFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
