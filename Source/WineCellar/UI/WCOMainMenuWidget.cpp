// Fill out your copyright notice in the Description page of Project Settings.

#include "WCOMainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "WineCellar/Game/WCOGameInstance.h"

void UWCOMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Btn_NewGame) Btn_NewGame->OnClicked.AddDynamic(this, &UWCOMainMenuWidget::OnNewGameClicked);
	if (Btn_Continue) Btn_Continue->OnClicked.AddDynamic(this, &UWCOMainMenuWidget::OnContinueClicked);
	if (Btn_LoadGame) Btn_LoadGame->OnClicked.AddDynamic(this, &UWCOMainMenuWidget::OnLoadGameClicked);
	if (Btn_Settings) Btn_Settings->OnClicked.AddDynamic(this, &UWCOMainMenuWidget::OnSettingsClicked);
	if (Btn_Credits) Btn_Credits->OnClicked.AddDynamic(this, &UWCOMainMenuWidget::OnCreditsClicked);
	if (Btn_Quit) Btn_Quit->OnClicked.AddDynamic(this, &UWCOMainMenuWidget::OnQuitClicked);
	
	if (Btn_Continue)
	{
		if (UWCOGameInstance* GI = Cast<UWCOGameInstance>(GetGameInstance()))
		{
			if (GI->GetContinueSlotIndex() == -1)
			{
				Btn_Continue->SetVisibility(ESlateVisibility::Collapsed);
				UE_LOG(LogTemp, Warning, TEXT("COLLAPSED"));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Visible"));
				Btn_Continue->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
}

void UWCOMainMenuWidget::OnNewGameClicked()
{
	// 1. Grab the Master UI instance from your HUD
	// 2. Instantiate your USaveMenuWidget
	// 3. Call MasterUIInstance->PushWidgetToOverlay(SaveMenuWidget)
}

void UWCOMainMenuWidget::OnContinueClicked()
{
	if (UWCOGameInstance* GI = Cast<UWCOGameInstance>(GetGameInstance()))
	{
		const int32 SlotToContinue = GI->GetContinueSlotIndex();

		if (SlotToContinue != -1)
		{
			// Load the data into memory
			GI->LoadGame(SlotToContinue);

			// Open the Cellar map
			UGameplayStatics::OpenLevel(this, FName("Map_Cellar_01"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No save files found to continue!"));
		}
	}
}

void UWCOMainMenuWidget::OnLoadGameClicked()
{
	// We will push USaveMenuWidget (the 3-slot menu) to the Master UI overlay here later
}

void UWCOMainMenuWidget::OnSettingsClicked()
{
	// Push Settings widget
}

void UWCOMainMenuWidget::OnCreditsClicked()
{
	// Push a WBP_Credits widget to the MasterUI overlay later!
}

void UWCOMainMenuWidget::OnQuitClicked()
{
	// Quit game
}