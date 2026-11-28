// Fill out your copyright notice in the Description page of Project Settings.

#include "WCOGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "WineCellar/SaveGame/WCOSaveGame.h"

FString UWCOGameInstance::GetSlotName(int32 SlotIndex) const
{
	return FString::Printf(TEXT("CellarSlot_%d"), SlotIndex);
}

void UWCOGameInstance::CreateNewGame(int32 SlotIndex, const FString& CustomSaveName)
{
	// 1. Create a brand new, empty SaveGame object
	UWCOSaveGame* NewSave = Cast<UWCOSaveGame>(UGameplayStatics::CreateSaveGameObject(UWCOSaveGame::StaticClass()));
	
	if (NewSave)
	{
		// 2. Set the initial defaults
		NewSave->SaveSlotName = CustomSaveName;
		NewSave->LastSaveTime = FDateTime::Now();
		NewSave->SommelierRank = 1;
		NewSave->TotalMoney = 0.0f;

		// 3. Save it to the hard drive
		UGameplayStatics::SaveGameToSlot(NewSave, GetSlotName(SlotIndex), 0);

		// 4. Set it as our active memory state
		CurrentSaveData = NewSave;
		CurrentSlotIndex = SlotIndex;
	}
}

bool UWCOGameInstance::LoadGame(int32 SlotIndex)
{
	const FString TargetSlot = GetSlotName(SlotIndex);

	// 1. Check if the file actually exists on the hard drive
	if (UGameplayStatics::DoesSaveGameExist(TargetSlot, 0))
	{
		// 2. Load it and cast it to our custom class
		if (UWCOSaveGame* LoadedSave = Cast<UWCOSaveGame>(UGameplayStatics::LoadGameFromSlot(TargetSlot, 0)))
		{
			CurrentSaveData = LoadedSave;
			CurrentSlotIndex = SlotIndex;
			return true;
		}
	}
	return false;
}

void UWCOGameInstance::SaveGame()
{
	if (CurrentSaveData && CurrentSlotIndex != -1)
	{
		// 1. Update the timestamp so "Continue" always grabs the newest one
		CurrentSaveData->LastSaveTime = FDateTime::Now();

		// 2. Write the memory state to the hard drive
		UGameplayStatics::SaveGameToSlot(CurrentSaveData, GetSlotName(CurrentSlotIndex), 0);
	}
}

int32 UWCOGameInstance::GetContinueSlotIndex()
{
	int32 NewestSlot = -1;
	FDateTime NewestTime = FDateTime::MinValue();

	// Loop strictly through slots 1, 2, and 3
	for (int32 i = 1; i <= 3; i++)
	{
		FString TargetSlot = GetSlotName(i);

		if (UGameplayStatics::DoesSaveGameExist(TargetSlot, 0))
		{
			// Load just the header data to check the time
			if (const UWCOSaveGame* TempSave = Cast<UWCOSaveGame>(UGameplayStatics::LoadGameFromSlot(TargetSlot, 0)))
			{
				if (TempSave->LastSaveTime > NewestTime)
				{
					NewestTime = TempSave->LastSaveTime;
					NewestSlot = i;
				}
			}
		}
	}

	return NewestSlot; 
}
