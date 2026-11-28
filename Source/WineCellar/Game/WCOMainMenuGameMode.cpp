// Fill out your copyright notice in the Description page of Project Settings.

#include "WCOMainMenuGameMode.h"
#include "WineCellar/UI/WCOHUD.h"

AWCOMainMenuGameMode::AWCOMainMenuGameMode()
{
	// Tell the game mode to use our custom HUD class by default
	HUDClass = AWCOHUD::StaticClass();
}
