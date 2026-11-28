// Fill out your copyright notice in the Description page of Project Settings.

#include "WCOHUD.h"
#include "WCOMasterUI.h"

void AWCOHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MasterUIClass)
	{
		MasterUIInstance = CreateWidget<UWCOMasterUI>(GetWorld(), MasterUIClass);
		if (MasterUIInstance)
		{
			MasterUIInstance->AddToViewport();
		}
	}
}
