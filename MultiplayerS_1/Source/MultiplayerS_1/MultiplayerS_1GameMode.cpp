// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MultiplayerS_1GameMode.h"
#include "MultiplayerS_1Character.h"
#include "UObject/ConstructorHelpers.h"

AMultiplayerS_1GameMode::AMultiplayerS_1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
