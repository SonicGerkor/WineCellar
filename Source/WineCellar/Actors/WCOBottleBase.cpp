// Fill out your copyright notice in the Description page of Project Settings.

#include "WCOBottleBase.h"

#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "WineCellar/Character/WCOCharacter.h"
#include "WineCellar/Label/WCOLabelWidget.h"

AWCOBottleBase::AWCOBottleBase()
{
	PrimaryActorTick.bCanEverTick = false;

	BottleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BottleMesh"));
	RootComponent = BottleMesh;
	BottleMesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	LabelWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("LabelWidget"));
	
	if (LabelWidgetComponent)
	{
		LabelWidgetComponent->SetupAttachment(BottleMesh);
		LabelWidgetComponent->SetDrawSize(FVector2D(512, 512));
		LabelWidgetComponent->SetRelativeScale3D(FVector(0.001f));;
	}
}

void AWCOBottleBase::BeginPlay()
{
	Super::BeginPlay();
}

void AWCOBottleBase::InitializeWine(const FWineData& InData)
{
	BottleData = InData;

	if (LabelWidgetComponent)
	{
		LabelWidgetComponent->InitWidget();
		if (UWCOLabelWidget* LabelWidget = Cast<UWCOLabelWidget>(LabelWidgetComponent->GetUserWidgetObject()))
		{
			LabelWidget->UpdateLabelData(BottleData);
			LabelWidgetComponent->RequestRedraw();
		}

		if (BottleMesh->GetMaterial(0))
		{
			BottleMID = BottleMesh->CreateAndSetMaterialInstanceDynamic(0);
			if (BottleMID && LabelWidgetComponent->GetRenderTarget())
			{
				BottleMID->SetTextureParameterValue(TEXT("LabelTexture"), LabelWidgetComponent->GetRenderTarget());
			}
		}
	}
}

void AWCOBottleBase::OnPickedUp(USceneComponent* AttachToComponent)
{
	if (!AttachToComponent) return;

	BottleMesh->SetSimulatePhysics(false);
	BottleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToActor(AttachToComponent->GetOwner(), AttachmentRules);
	BottleMesh->AttachToComponent(AttachToComponent, AttachmentRules);

	SetActorTickEnabled(false);
}

void AWCOBottleBase::OnPlaced()
{
	const FDetachmentTransformRules DetachmentRules(EDetachmentRule::KeepWorld, true);
	DetachFromActor(DetachmentRules);
	BottleMesh->DetachFromComponent(DetachmentRules);

	BottleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BottleMesh->SetSimulatePhysics(false); 

	SetActorTickEnabled(false);
}

void AWCOBottleBase::Interact(AWCOCharacter* Interactor)
{
	// Only allow grabbing if the player's hands are empty
	if (Interactor && Interactor->GetHeldBottle() == nullptr)
	{
		// 1. Turn off physics so it doesn't violently ragdoll in the player's hand
		if (BottleMesh)
		{
			BottleMesh->SetSimulatePhysics(false);
			BottleMesh->SetCollisionProfileName(TEXT("NoCollision"));
		}

		// 2. Attach the bottle to the player's camera or a specific socket
		AttachToComponent(Interactor->GetFirstPersonCameraComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		
		// 3. Offset the bottle so it sits nicely in the bottom right of the screen (simulating holding it)
		SetActorRelativeLocation(FVector(40.f, 20.f, -30.f));
		SetActorRelativeRotation(FRotator(0.f, 0.f, 0.f));

		// 4. Tell the player they are now officially holding this bottle
		Interactor->SetHeldBottle(this);
	}
}

void AWCOBottleBase::Highlight()
{
	if (BottleMesh)
	{
		BottleMesh->SetRenderCustomDepth(true);
		
		// Optional: Set a specific stencil value (e.g., 1 for green outline, 2 for red)
		BottleMesh->SetCustomDepthStencilValue(1); 
	}
}

void AWCOBottleBase::Unhighlight()
{
	if (BottleMesh)
	{
		BottleMesh->SetRenderCustomDepth(false);
	}
}
