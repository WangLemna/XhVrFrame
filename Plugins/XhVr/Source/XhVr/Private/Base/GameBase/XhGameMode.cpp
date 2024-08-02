// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/GameBase/XhGameMode.h"
#include "Base/GameBase/XhGameState.h"
#include "Base/GameBase/XhPlayerController.h"
#include "Base/GameBase/XhPlayerState.h"
#include "Base/GameBase/XhCharacter.h"

AXhGameMode::AXhGameMode()
{
	GameStateClass = AXhGameState::StaticClass();
	PlayerControllerClass = AXhPlayerController::StaticClass();
	PlayerStateClass = AXhPlayerState::StaticClass();
	DefaultPawnClass = AXhCharacter::StaticClass();
}
