// Copyright Epic Games, Inc. All Rights Reserved.

#include "WebSocketTest2GameMode.h"
#include "WebSocketTest2Character.h"
#include "UObject/ConstructorHelpers.h"

AWebSocketTest2GameMode::AWebSocketTest2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
