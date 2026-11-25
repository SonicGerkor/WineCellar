// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WCOBottleBase.generated.h"

class UStaticMeshComponent;

UENUM(BlueprintType)
enum class EBottleStyle : uint8
{
	None			UMETA(DisplayName = "None"),
	Bordeaux		UMETA(DisplayName = "Bordeaux (Standard)"),
	Burgundy		UMETA(DisplayName = "Burgundy (Sloped)"),
	Flute			UMETA(DisplayName = "Flute (High-Shouldered)"),
	Champagne		UMETA(DisplayName = "Champagne (Heavy)"),
	Magnum			UMETA(DisplayName = "Magnum (1.5L)"),
	Jeroboam		UMETA(DisplayName = "Jeroboam (3.0L)")
};

UENUM(BlueprintType)
enum class EWineGrape : uint8
{
	None			UMETA(DisplayName = "None"),
	Malbec			UMETA(DisplayName = "Malbec"),
	CabernetFranc	UMETA(DisplayName = "Cabernet Franc"),
	PinotNoir		UMETA(DisplayName = "Pinot Noir"),
	Chardonnay		UMETA(DisplayName = "Chardonnay")
};

UENUM(BlueprintType)
enum class EWineRegion : uint8
{
	None			UMETA(DisplayName = "None"),
	Mendoza			UMETA(DisplayName = "Mendoza"),
	Bordeaux		UMETA(DisplayName = "Bordeaux"),
	NapaValley		UMETA(DisplayName = "Napa Valley")
};

USTRUCT(BlueprintType)
struct FWineData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wine Details")
	EWineGrape GrapeType = EWineGrape::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wine Details")
	EWineRegion Region = EWineRegion::None;

	// The physical style/size of the bottle mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wine Details")
	EBottleStyle BottleStyle = EBottleStyle::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wine Details")
	int32 VintageYear = 2020;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wine Details")
	FString BrandName = TEXT("Generic Estate");
};

UCLASS()
class WINECELLAR_API AWCOBottleBase : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AWCOBottleBase();

	// The spatial representation of the bottle
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* BottleMesh;

	// The data payload for this specific bottle instance
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (ExposeOnSpawn = "true"))
	FWineData BottleData;

	// State changes for grabbing and placing
	void OnPickedUp(USceneComponent* AttachToComponent);
	void OnPlaced();

	// Getter for the shelf logic to validate placement
	FORCEINLINE FWineData GetBottleData() const { return BottleData; }
};
