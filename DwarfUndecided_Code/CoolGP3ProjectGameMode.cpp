// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoolGP3ProjectGameMode.h"
#include "CoolGP3ProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACoolGP3ProjectGameMode::ACoolGP3ProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
