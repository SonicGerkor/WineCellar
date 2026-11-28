// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WCOMasterUI.generated.h"

class UCanvasPanel;
class UOverlay;

UCLASS()
class WINECELLAR_API UWCOMasterUI : public UUserWidget
{
	GENERATED_BODY()

public:
	
	// The ONLY Canvas Panel in the entire project
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* RootCanvas;

	// The container where we will inject the Main Menu, Inventory, or Save Menu
	UPROPERTY(meta = (BindWidget))
	UOverlay* ActiveViewOverlay;

	// Helper function to push small WBPs into the overlay
	UFUNCTION(BlueprintCallable, Category = "UI")
	void PushWidgetToOverlay(UUserWidget* NewWidget);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ClearOverlay();
};
