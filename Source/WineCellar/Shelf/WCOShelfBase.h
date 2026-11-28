// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WineCellar/Interfaces/WCOInteractable.h"
#include "WCOShelfBase.generated.h"

class UStaticMeshComponent;
class UWCOSlotComponent;

UCLASS()
class WINECELLAR_API AWCOShelfBase : public AActor, public IWCOInteractable
{
	GENERATED_BODY()
	
public:	
	
	AWCOShelfBase();
	
	virtual void Interact(AWCOCharacter* Interactor) override;
	virtual void Highlight() override;
	virtual void Unhighlight() override;

protected:
	
	virtual void BeginPlay() override;

public:	
	
	// The physical frame of the shelf
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* ShelfMesh;

	// Dynamically populated array of all slots attached to this shelf
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slots")
	TArray<UWCOSlotComponent*> ShelfSlots;
};
