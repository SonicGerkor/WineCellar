// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "WCOHUD.generated.h"

class UWCOMasterUI;

UCLASS()
class WINECELLAR_API AWCOHUD : public AHUD
{
	GENERATED_BODY()

public:
	
	// Expose to BP so we can assign WBP_MasterUI
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UWCOMasterUI> MasterUIClass;

	// We keep a pointer to it so we can push/pop widgets globally from anywhere
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	UWCOMasterUI* MasterUIInstance;
	
protected:
	
	virtual void BeginPlay() override;
};
