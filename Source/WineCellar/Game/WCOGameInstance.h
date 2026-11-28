// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "WCOGameInstance.generated.h"

class UWCOSaveGame;

UCLASS()
class WINECELLAR_API UWCOGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	
	// The SaveGame object currently loaded into memory
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save System")
	UWCOSaveGame* CurrentSaveData;

	// The slot ID (1, 2, or 3) we are currently playing on
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save System")
	int32 CurrentSlotIndex = -1;

	// Creates a blank save file on a specific slot with a custom name
	UFUNCTION(BlueprintCallable, Category = "Save System")
	void CreateNewGame(int32 SlotIndex, const FString& CustomSaveName);

	// Loads a specific slot into memory (returns true if successful)
	UFUNCTION(BlueprintCallable, Category = "Save System")
	bool LoadGame(int32 SlotIndex);

	// Saves the active memory state back to the hard drive
	UFUNCTION(BlueprintCallable, Category = "Save System")
	void SaveGame();

	// Checks slots 1, 2, and 3 to find the one with the newest LastSaveTime
	UFUNCTION(BlueprintCallable, Category = "Save System")
	int32 GetContinueSlotIndex();

private:
	
	FString GetSlotName(int32 SlotIndex) const;
};
