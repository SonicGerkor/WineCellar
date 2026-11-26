// Fill out your copyright notice in the Description page of Project Settings.

#include "WCOLabelWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"

void UWCOLabelWidget::UpdateLabelData(const FWineData& BottleData)
{
	// 1. Direct String Updates
	if (Text_BrandName)
	{
		Text_BrandName->SetText(FText::FromString(BottleData.BrandName));
	}

	if (Text_Vintage)
	{
		Text_Vintage->SetText(FText::FromString(FString::FromInt(BottleData.VintageYear)));
	}

	// 2. Convert Enums to Strings via Reflection
	if (Text_Grape)
	{
		const UEnum* GrapeEnum = StaticEnum<EWineGrape>();
		if (GrapeEnum)
		{
			// Gets the Display Name (e.g., "Cabernet Franc" instead of just "CabernetFranc")
			const FText GrapeDisplayName = GrapeEnum->GetDisplayNameTextByValue(static_cast<int64>(BottleData.GrapeType));
			Text_Grape->SetText(GrapeDisplayName);
		}
	}

	if (Text_Region)
	{
		const UEnum* RegionEnum = StaticEnum<EWineRegion>();
		if (RegionEnum)
		{
			const FText RegionDisplayName = RegionEnum->GetDisplayNameTextByValue(static_cast<int64>(BottleData.Region));
			Text_Region->SetText(RegionDisplayName);
		}
	}

	// 3. Image/Logo Update
	if (Image_Logo && BottleData.LogoTexture)
	{
		Image_Logo->SetBrushFromTexture(BottleData.LogoTexture);
	}
}
