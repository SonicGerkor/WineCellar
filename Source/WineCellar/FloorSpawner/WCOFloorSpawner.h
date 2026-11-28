// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WineCellar/Actors/WCOWineDBEnums.h"
#include "WCOFloorSpawner.generated.h"

class AWCOBottleBase;
class UBoxComponent;
class UDataTable;

UCLASS()
class WINECELLAR_API AWCOFloorSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AWCOFloorSpawner();

protected:
	virtual void BeginPlay() override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawner")
	UBoxComponent* SpawnVolume;

	// The Master CSV Database
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Config")
	UDataTable* WineDatabase;

	// The Blueprint class to spawn (BP_Bottle_Base)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Config")
	TSubclassOf<AWCOBottleBase> BottleClass;

	// How many bottles to drop on the floor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Config", meta = (ClampMin = "1"))
	int32 TotalBottlesToSpawn = 10;

	// --- DESIGNER FILTERS ---
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Filters")
	bool bFilterByGrape = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Filters", meta = (EditCondition = "bFilterByGrape"))
	EWineGrape TargetGrape = EWineGrape::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Filters")
	bool bFilterByRegion = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Filters", meta = (EditCondition = "bFilterByRegion"))
	EWineRegion TargetRegion = EWineRegion::None;
};
