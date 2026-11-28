// Fill out your copyright notice in the Description page of Project Settings.

#include "WCOShelfBase.h"
#include "WCOSlotComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "WineCellar/Character/WCOCharacter.h"

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

void AWCOShelfBase::Interact(AWCOCharacter* Interactor)
{
	// Only allow placement if the player is actually holding a bottle
	if (Interactor && Interactor->GetHeldBottle() != nullptr)
	{
		UWCOSlotComponent* ClosestSlot = nullptr;
		float ClosestDistSq = MAX_flt;

		// 2. We use the camera's location as the center of our search
		const FVector SearchOrigin = Interactor->GetFirstPersonCameraComponent()->GetComponentLocation();

		for (UWCOSlotComponent* Slot : ShelfSlots)
		{
			if (Slot && !Slot->bIsOccupied) 
			{
				const float DistSq = FVector::DistSquared(SearchOrigin, Slot->GetComponentLocation());
				
				if (DistSq < ClosestDistSq && DistSq < 2500.f) // 50cm limit
				{
					ClosestDistSq = DistSq;
					ClosestSlot = Slot;
				}
			}
		}

		// 3. We found a slot! Execute placement.
		if (ClosestSlot)
		{
			AWCOBottleBase* BottleToPlace = Interactor->GetHeldBottle();

			// Lay it flat (using the fix we discussed earlier)
			BottleToPlace->BottleMesh->AttachToComponent(ClosestSlot, FAttachmentTransformRules::KeepRelativeTransform);
			BottleToPlace->SetActorRelativeRotation(FRotator(90.f, 0.f, 0.f));
			BottleToPlace->SetActorRelativeLocation(FVector(15.f, 0.f, 0.f)); 
			
			// Optional: Turn collision back on so it blocks other things, but keep physics OFF
			BottleToPlace->BottleMesh->SetCollisionProfileName(TEXT("BlockAll"));

			// Update states
			ClosestSlot->bIsOccupied = true;
			Interactor->SetHeldBottle(nullptr);
		}
	}
}

void AWCOShelfBase::Highlight() {}

void AWCOShelfBase::Unhighlight() {}
