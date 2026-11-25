// Fill out your copyright notice in the Description page of Project Settings.

#include "WCOCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DrawDebugHelpers.h"
#include "WineCellar/Actors/WCOBottleBase.h"
#include "WineCellar/Shelf/WCOSlotComponent.h"

AWCOCharacter::AWCOCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0.f, 0.f, 64.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a scene component to act as the attachment point for grabbed bottles
	HeldItemLocation = CreateDefaultSubobject<USceneComponent>(TEXT("HeldItemLocation"));
	HeldItemLocation->SetupAttachment(FirstPersonCameraComponent);
	HeldItemLocation->SetRelativeLocation(FVector(50.0f, 20.0f, -15.0f));

	CurrentHeldBottle = nullptr;
}

void AWCOCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Add Enhanced Input Mapping Context
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
}

void AWCOCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AWCOCharacter::Move);
		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AWCOCharacter::Look);
		// Interacting (Grab/Place)
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AWCOCharacter::Interact);
	}
}

void AWCOCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Add movement in forward and right directions
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AWCOCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AWCOCharacter::Interact()
{
	const FVector Start = FirstPersonCameraComponent->GetComponentLocation();
	const FVector End = Start + (FirstPersonCameraComponent->GetForwardVector() * InteractionDistance);
	
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	if (CurrentHeldBottle)
	{
		// 1. PLACE BOTTLE LOGIC
		
		// CRITICAL: Ignore the bottle we are currently holding, or the raycast will hit it
		QueryParams.AddIgnoredActor(CurrentHeldBottle);

		const bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams);

		if (bHit)
		{
			if (UWCOSlotComponent* HitSlot = Cast<UWCOSlotComponent>(HitResult.GetComponent()))
			{
				// Validates placement rules; incorrect placement is mechanically blocked here
				if (!HitSlot->bIsOccupied && HitSlot->IsValidPlacement(CurrentHeldBottle->GetBottleData()))
				{
					CurrentHeldBottle->OnPlaced();
					
					// Snap the bottle exactly to the slot's transform
					CurrentHeldBottle->SetActorTransform(HitSlot->GetComponentTransform());
					
					HitSlot->bIsOccupied = true;
					HitSlot->CurrentBottle = CurrentHeldBottle;
					CurrentHeldBottle = nullptr;
					
					UE_LOG(LogTemp, Warning, TEXT("Bottle permanently placed successfully!"));
				}
			}
		}
	}
	else
	{
		// 2. GRAB BOTTLE LOGIC

		const bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams);
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f, 0, 1.0f);
		if (bHit && HitResult.GetActor())
		{
			if (AWCOBottleBase* HitBottle = Cast<AWCOBottleBase>(HitResult.GetActor()))
			{
				HitBottle->OnPickedUp(HeldItemLocation);
				CurrentHeldBottle = HitBottle;
				
				UE_LOG(LogTemp, Warning, TEXT("Picked up bottle!"));
			}
		}
	}
}
