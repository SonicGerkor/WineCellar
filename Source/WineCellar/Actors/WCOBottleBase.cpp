// Fill out your copyright notice in the Description page of Project Settings.

#include "WCOBottleBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/TextureRenderTarget2D.h"
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
