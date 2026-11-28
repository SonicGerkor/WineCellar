// Fill out your copyright notice in the Description page of Project Settings.

#include "WCOFloorSpawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/DataTable.h"
#include "WineCellar/Actors/WCOBottleBase.h"

AWCOFloorSpawner::AWCOFloorSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	RootComponent = SpawnVolume;
	
	// Default size: 2 meters by 2 meters, 50cm tall
	SpawnVolume->SetBoxExtent(FVector(100.f, 100.f, 25.f));
	
	// Ensure the invisible box doesn't block player movement or raycasts
	SpawnVolume->SetCollisionProfileName(TEXT("NoCollision"));
}

void AWCOFloorSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (!WineDatabase || !BottleClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Spawner %s is missing Database or BottleClass!"), *GetName());
		return;
	}

	// 1. Fetch every single row from the CSV
	TArray<FWineData*> AllWines;
	WineDatabase->GetAllRows<FWineData>(TEXT("FloorSpawnerContext"), AllWines);

	// 2. Apply Filters
	TArray<FWineData*> ValidWines;
	for (FWineData* WineData : AllWines)
	{
		bool bIsValid = true;

		if (bFilterByGrape && WineData->GrapeType != TargetGrape)
		{
			bIsValid = false;
		}
		if (bFilterByRegion && WineData->Region != TargetRegion)
		{
			bIsValid = false;
		}

		if (bIsValid)
		{
			ValidWines.Add(WineData);
		}
	}

	if (ValidWines.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawner %s found NO wines matching the filters!"), *GetName());
		return;
	}

	// 3. Scatter and Spawn
	for (int32 i = 0; i < TotalBottlesToSpawn; i++)
	{
		// Pick a random wine from our filtered pool
		const int32 RandomIndex = FMath::RandRange(0, ValidWines.Num() - 1);
		const FWineData* SelectedWine = ValidWines[RandomIndex];

		// Calculate a random location inside the Box Component
		FVector RandomLocation = UKismetMathLibrary::RandomPointInBoundingBox(
			SpawnVolume->GetComponentLocation(), 
			SpawnVolume->GetScaledBoxExtent()
		);

		// Slight random rotation so they look naturally dropped
		FRotator RandomRotation = FRotator(FMath::RandRange(0.f, 360.f), FMath::RandRange(0.f, 360.f), FMath::RandRange(0.f, 360.f));

		// Spawn it
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
		if (AWCOBottleBase* NewBottle = GetWorld()->SpawnActor<AWCOBottleBase>(BottleClass, RandomLocation, RandomRotation, SpawnParams))
		{
			// Inject the data to build the label and materials!
			NewBottle->InitializeWine(*SelectedWine);
		}
	}
}
