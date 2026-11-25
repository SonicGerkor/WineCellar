// Fill out your copyright notice in the Description page of Project Settings.

#include "WCOBottleBase.h"
#include "Components/StaticMeshComponent.h"

AWCOBottleBase::AWCOBottleBase()
{
	PrimaryActorTick.bCanEverTick = false;

	BottleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BottleMesh"));
	RootComponent = BottleMesh;

	// Ensure the mesh blocks the line trace from the character's camera
	BottleMesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	
	// Optional: Enable physics for when it drops or rolls, though for a strict 
	// organization game, you might prefer kinematic snapping.
	BottleMesh->SetSimulatePhysics(true);
}

void AWCOBottleBase::OnPickedUp(USceneComponent* AttachToComponent)
{
	if (!AttachToComponent) return;

	// Disable physics and collision so it doesn't bump the player while held
	BottleMesh->SetSimulatePhysics(false);
	BottleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Attach to the player's holding socket
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToActor(AttachToComponent->GetOwner(), AttachmentRules);
	
	// Specifically attach the mesh to the target scene component
	BottleMesh->AttachToComponent(AttachToComponent, AttachmentRules);
}

void AWCOBottleBase::OnPlaced()
{
	FDetachmentTransformRules DetachmentRules(EDetachmentRule::KeepWorld, true);
	DetachFromActor(DetachmentRules);
	BottleMesh->DetachFromComponent(DetachmentRules);

	// Disable collision completely so the player's line trace can never pick it up again
	BottleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BottleMesh->SetSimulatePhysics(false);
}
