// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WCOWineDBEnums.h"
#include "GameFramework/Actor.h"
#include "WineCellar/Interfaces/WCOInteractable.h"
#include "WCOBottleBase.generated.h"

class UWidgetComponent;
class UStaticMeshComponent;

USTRUCT(BlueprintType)
struct FWineData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wine Details")
	EWineGrape GrapeType = EWineGrape::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wine Details")
	EWineRegion Region = EWineRegion::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wine Details")
	EBottleStyle BottleStyle = EBottleStyle::Bordeaux;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wine Details")
	int32 VintageYear = 2020;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wine Details")
	FString BrandName = TEXT("Generic Estate");

	// NEW: The logo texture for the label widget to use
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wine Details")
	UTexture2D* LogoTexture = nullptr;
};

UCLASS()
class WINECELLAR_API AWCOBottleBase : public AActor, public IWCOInteractable
{
	GENERATED_BODY()
	
public:	
	
	AWCOBottleBase();
	
	virtual void Interact(AWCOCharacter* Interactor) override;
	virtual void Highlight() override;
	virtual void Unhighlight() override;

	// The spatial representation of the bottle
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* BottleMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWidgetComponent* LabelWidgetComponent;
	
	// Add this new function:
	UFUNCTION(BlueprintCallable, Category = "Initialization")
	void InitializeWine(const FWineData& InData);

	// State changes for grabbing and placing
	void OnPickedUp(USceneComponent* AttachToComponent);
	void OnPlaced();

	// Getter for the shelf logic to validate placement
	FORCEINLINE FWineData GetBottleData() const { return BottleData; }
	
protected:
	
	virtual void BeginPlay() override;
	
	FWineData BottleData;
	
private:
	
	UPROPERTY()
	UMaterialInstanceDynamic* BottleMID;
};
