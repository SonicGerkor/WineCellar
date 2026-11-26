// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WCOWineDBEnums.generated.h"

UENUM(BlueprintType)
enum class EWineGrape : uint8
{
	None				UMETA(DisplayName = "None"),
	CabernetSauvignon	UMETA(DisplayName = "Cabernet Sauvignon"),
	Merlot				UMETA(DisplayName = "Merlot"),
	CabernetFranc		UMETA(DisplayName = "Cabernet Franc"),
	PetitVerdot			UMETA(DisplayName = "Petit Verdot"),
	Malbec				UMETA(DisplayName = "Malbec"),
	Carmenere			UMETA(DisplayName = "Carménère"),
	PinotNoir			UMETA(DisplayName = "Pinot Noir"),
	Syrah				UMETA(DisplayName = "Syrah"),
	Grenache			UMETA(DisplayName = "Grenache"),
	Mourvedre			UMETA(DisplayName = "Mourvèdre"),
	Sangiovese			UMETA(DisplayName = "Sangiovese"),
	Nebbiolo			UMETA(DisplayName = "Nebbiolo"),
	Barbera				UMETA(DisplayName = "Barbera"),
	Tempranillo			UMETA(DisplayName = "Tempranillo"),
	Zinfandel			UMETA(DisplayName = "Zinfandel"),
	Primitivo			UMETA(DisplayName = "Primitivo"),
	Chardonnay			UMETA(DisplayName = "Chardonnay"),
	SauvignonBlanc		UMETA(DisplayName = "Sauvignon Blanc"),
	Semillon			UMETA(DisplayName = "Sémillon"),
	Riesling			UMETA(DisplayName = "Riesling"),
	CheninBlanc			UMETA(DisplayName = "Chenin Blanc"),
	Viognier			UMETA(DisplayName = "Viognier"),
	PinotGris			UMETA(DisplayName = "Pinot Gris"),
	Gewurztraminer		UMETA(DisplayName = "Gewürztraminer"),
	Muscat				UMETA(DisplayName = "Muscat"),
	Albarino			UMETA(DisplayName = "Albariño"),
	GrunerVeltliner		UMETA(DisplayName = "Grüner Veltliner"),
	Glera				UMETA(DisplayName = "Glera"),
	Trebbiano			UMETA(DisplayName = "Trebbiano"),
	Garganega			UMETA(DisplayName = "Garganega"),
	Cortese				UMETA(DisplayName = "Cortese"),
	Torrontes			UMETA(DisplayName = "Torrontés"),
	Shiraz				UMETA(DisplayName = "Shiraz"),
	PetitManseng		UMETA(DisplayName = "Petit Manseng"),
	Tannat				UMETA(DisplayName = "Tannat"),
	TourigaNacional		UMETA(DisplayName = "Touriga Nacional"),
	Verdejo				UMETA(DisplayName = "Verdejo"),
	Macabeo				UMETA(DisplayName = "Macabeo"),
	Aglianico			UMETA(DisplayName = "Aglianico"),
	NeroDAvola			UMETA(DisplayName = "Nero d'Avola")
};

UENUM(BlueprintType)
enum class EWineRegion : uint8
{
	None			UMETA(DisplayName = "None"),
	Bordeaux		UMETA(DisplayName = "Bordeaux"),
	Burgundy		UMETA(DisplayName = "Burgundy"),
	Champagne		UMETA(DisplayName = "Champagne"),
	RhoneValley		UMETA(DisplayName = "Rhône Valley"),
	LoireValley		UMETA(DisplayName = "Loire Valley"),
	Alsace			UMETA(DisplayName = "Alsace"),
	NapaValley		UMETA(DisplayName = "Napa Valley"),
	SonomaCounty	UMETA(DisplayName = "Sonoma County"),
	WillametteValley UMETA(DisplayName = "Willamette Valley"),
	Mendoza			UMETA(DisplayName = "Mendoza"),
	Patagonia		UMETA(DisplayName = "Patagonia"),
	Salta			UMETA(DisplayName = "Salta"),
	Tuscany			UMETA(DisplayName = "Tuscany"),
	Piedmont		UMETA(DisplayName = "Piedmont"),
	Veneto			UMETA(DisplayName = "Veneto"),
	Sicily			UMETA(DisplayName = "Sicily"),
	Rioja			UMETA(DisplayName = "Rioja"),
	RiberaDelDuero	UMETA(DisplayName = "Ribera del Duero"),
	Priorat			UMETA(DisplayName = "Priorat"),
	RiasBaixas		UMETA(DisplayName = "Rías Baixas"),
	BarossaValley	UMETA(DisplayName = "Barossa Valley"),
	McLarenVale		UMETA(DisplayName = "McLaren Vale"),
	MargaretRiver	UMETA(DisplayName = "Margaret River"),
	Marlborough		UMETA(DisplayName = "Marlborough"),
	CentralOtago	UMETA(DisplayName = "Central Otago"),
	Stellenbosch	UMETA(DisplayName = "Stellenbosch"),
	Mosel			UMETA(DisplayName = "Mosel"),
	MaipoValley		UMETA(DisplayName = "Maipo Valley"),
	ColchaguaValley	UMETA(DisplayName = "Colchagua Valley"),
	Douro			UMETA(DisplayName = "Douro")
};

UENUM(BlueprintType)
enum class EBottleStyle : uint8
{
	Bordeaux	UMETA(DisplayName = "Bordeaux"),
	Burgundy	UMETA(DisplayName = "Burgundy"),
	Flute		UMETA(DisplayName = "Flute"),
	Champagne	UMETA(DisplayName = "Champagne")
};
