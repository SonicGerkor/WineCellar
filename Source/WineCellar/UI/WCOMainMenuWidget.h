// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WCOMainMenuWidget.generated.h"

class UButton;

UCLASS()
class WINECELLAR_API UWCOMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UButton* Btn_NewGame;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Btn_Continue;

	UPROPERTY(meta = (BindWidget))
	UButton* Btn_LoadGame; 

	UPROPERTY(meta = (BindWidget))
	UButton* Btn_Settings;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Btn_Credits;

	UPROPERTY(meta = (BindWidget))
	UButton* Btn_Quit;

private:
	
	UFUNCTION() 
	void OnNewGameClicked();
	
	UFUNCTION() 
	void OnContinueClicked();
	
	UFUNCTION() 
	void OnLoadGameClicked();
	
	UFUNCTION() 
	void OnSettingsClicked();
	
	UFUNCTION() 
	void OnCreditsClicked();
	
	UFUNCTION() 
	void OnQuitClicked();
};
