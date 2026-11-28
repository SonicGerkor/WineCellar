// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "WCOSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FSavedBottleData
{
	GENERATED_BODY()

	// The row name from DT_WineDatabase so we know exactly what to spawn
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FName WineRowName;

	// Where is it in the world?
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FTransform WorldTransform;

	// Is it on a shelf? If so, which one, and in which slot?
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FName ParentShelfName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 ShelfSlotIndex;
};

UCLASS()
class WINECELLAR_API UWCOSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	// The custom name the player typed in (e.g., "My Awesome Cellar")
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save Data")
	FString SaveSlotName;

	// So we know which save is the most recent for the "Continue" button
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save Data")
	FDateTime LastSaveTime;

	// -- Player Profile --
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save Data|Profile")
	float TotalMoney;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save Data|Profile")
	int32 SommelierRank;

	// -- Cellar State --
	// The array that will hold the math for all 2,000 bottles
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save Data|Cellar")
	TArray<FSavedBottleData> SavedBottles;
};
