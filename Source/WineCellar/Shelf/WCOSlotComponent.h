// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "WineCellar/Actors/WCOBottleBase.h"
#include "WCOSlotComponent.generated.h"

class AWCOBottleBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WINECELLAR_API UWCOSlotComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	
	UWCOSlotComponent();

	// -- Validation Rules (Data-Oriented) --
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot Targets")
	EWineGrape AcceptedGrape = EWineGrape::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot Targets")
	EBottleStyle AcceptedStyle = EBottleStyle::Bordeaux;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot Targets")
	EWineRegion AcceptedRegion = EWineRegion::None;

	// -- State Tracking --
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slot State")
	bool bIsOccupied = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slot State")
	AWCOBottleBase* CurrentBottle = nullptr;

	// -- Functions --
	
	// Validates if a held bottle matches this slot's specific requirements
	UFUNCTION(BlueprintCallable, Category = "Slot Logic")
	bool IsValidPlacement(const FWineData& BottleData) const;
};
