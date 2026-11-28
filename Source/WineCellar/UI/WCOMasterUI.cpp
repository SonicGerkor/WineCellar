// Fill out your copyright notice in the Description page of Project Settings.

#include "WCOMasterUI.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"

void UWCOMasterUI::PushWidgetToOverlay(UUserWidget* NewWidget)
{
	if (ActiveViewOverlay && NewWidget)
	{
		ActiveViewOverlay->ClearChildren();
		UOverlaySlot* NewSlot = ActiveViewOverlay->AddChildToOverlay(NewWidget);
		
		// Ensure the injected widget fills the screen perfectly
		if (NewSlot)
		{
			NewSlot->SetHorizontalAlignment(HAlign_Fill);
			NewSlot->SetVerticalAlignment(VAlign_Fill);
		}
	}
}

void UWCOMasterUI::ClearOverlay()
{
	if (ActiveViewOverlay)
	{
		ActiveViewOverlay->ClearChildren();
	}
}
