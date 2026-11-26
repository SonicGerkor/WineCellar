// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WineCellar/Actors/WCOBottleBase.h"
#include "WCOLabelWidget.generated.h"

class UTextBlock;
class UImage;
class UTexture2D;

UCLASS()
class WINECELLAR_API UWCOLabelWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Label Generation")
	void UpdateLabelData(const FWineData& BottleData);

protected:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_BrandName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Grape;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Region;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Vintage;

	UPROPERTY(meta = (BindWidget))
	UImage* Image_Logo;
};
