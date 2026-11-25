// Fill out your copyright notice in the Description page of Project Settings.

#include "WCOGameModeBase.h"

AWCOGameModeBase::AWCOGameModeBase()
{
	// Default to no restrictions if this base class is accidentally used
	ActiveSortingMode = EWCOSortingMode::None;
}
