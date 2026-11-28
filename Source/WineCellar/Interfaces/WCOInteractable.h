// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WCOInteractable.generated.h"

class AWCOCharacter;

UINTERFACE(MinimalAPI)
class UWCOInteractable : public UInterface
{
	GENERATED_BODY()
};

class WINECELLAR_API IWCOInteractable
{
	GENERATED_BODY()

public:

	virtual void Interact(AWCOCharacter* Interactor) = 0;
	
	virtual void Highlight() = 0;
	virtual void Unhighlight() = 0;
};
