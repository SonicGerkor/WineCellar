// Fill out your copyright notice in the Description page of Project Settings.

#include "WCOSlotComponent.h"

#include "Kismet/GameplayStatics.h"
#include "WineCellar/Game/WCOGameModeBase.h"

UWCOSlotComponent::UWCOSlotComponent()
{
	// Set a default box extent roughly the size of a bottle for easy editor placement
	InitBoxExtent(FVector(10.0f, 10.0f, 20.0f));
	
	// Setup collision so the player's line trace can hit it when empty
	UBoxComponent::SetCollisionProfileName(TEXT("BlockAllDynamic"));
	
	// Optional: Set a distinct color for the wireframe box in the editor
	ShapeColor = FColor::Orange;
}

bool UWCOSlotComponent::IsValidPlacement(const FWineData& BottleData) const
{
	const AWCOGameModeBase* CurrentGM = Cast<AWCOGameModeBase>(UGameplayStatics::GetGameMode(this));
	
	if (!CurrentGM)
	{
		UE_LOG(LogTemp, Error, TEXT("No WCOGameModeBase found! Placement allowed by default."));
		return true;
	}

	// Route validation based on the active global rule
	switch (CurrentGM->GetActiveSortingMode())
	{
	case EWCOSortingMode::PerGrape:
		return BottleData.GrapeType == AcceptedGrape;

	case EWCOSortingMode::PerBottle:
		return BottleData.BottleStyle == AcceptedStyle;

	case EWCOSortingMode::PerRegion:
		return BottleData.Region == AcceptedRegion;

	case EWCOSortingMode::None:
	default:
		return true;
	}
}
