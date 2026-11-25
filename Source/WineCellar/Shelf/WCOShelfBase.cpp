// Fill out your copyright notice in the Description page of Project Settings.

#include "WCOShelfBase.h"
#include "WCOSlotComponent.h"
#include "Components/StaticMeshComponent.h"

AWCOShelfBase::AWCOShelfBase()
{
	PrimaryActorTick.bCanEverTick = false;

	ShelfMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShelfMesh"));
	RootComponent = ShelfMesh;
}

void AWCOShelfBase::BeginPlay()
{
	Super::BeginPlay();

	// Automatically find all slot components placed on this actor in the Blueprint Editor
	GetComponents<UWCOSlotComponent>(ShelfSlots);
	
	UE_LOG(LogTemp, Log, TEXT("Shelf %s initialized with %d slots."), *GetName(), ShelfSlots.Num());
}
