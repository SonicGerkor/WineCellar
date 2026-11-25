// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WCOGameModeBase.generated.h"

UENUM(BlueprintType)
enum class EWCOSortingMode : uint8
{
	None		UMETA(DisplayName = "None (Free Placement)"),
	PerGrape	UMETA(DisplayName = "Per Grape Variety"),
	PerBottle	UMETA(DisplayName = "Per Bottle Style"),
	PerRegion	UMETA(DisplayName = "Per Wine Location")
};

UCLASS()
class WINECELLAR_API AWCOGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	AWCOGameModeBase();

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sorting Rules")
	EWCOSortingMode ActiveSortingMode;

public:
	
	UFUNCTION(BlueprintCallable, Category = "Sorting Rules")
	EWCOSortingMode GetActiveSortingMode() const { return ActiveSortingMode; }
};
