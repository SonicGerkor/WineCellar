// Fill out your copyright notice in the Description page of Project Settings.

#include "WCOCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DrawDebugHelpers.h"
#include "WineCellar/Actors/WCOBottleBase.h"
#include "WineCellar/Shelf/WCOSlotComponent.h"
#include "WineCellar/Skills/WCOSkillComponent.h"

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
	
	SkillComponent = CreateDefaultSubobject<UWCOSkillComponent>(TEXT("SkillComponent"));

	HeldBottle = nullptr;
}

void AWCOCharacter::BeginPlay()
{
	Super::BeginPlay();

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
		
		// Jump
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}
}

void AWCOCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	PerformInteractionTrace();
}

void AWCOCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const float SpeedMultiplier = SkillComponent->GetModifierValue(ESkillModifierType::MovementSpeed);
		
		AddMovementInput(GetActorForwardVector(), MovementVector.Y * SpeedMultiplier);
		AddMovementInput(GetActorRightVector(), MovementVector.X * SpeedMultiplier);
	}
}

void AWCOCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AWCOCharacter::Interact()
{
	if (CurrentInteractable)
	{
		CurrentInteractable->Interact(this);
	}
}

void AWCOCharacter::PerformInteractionTrace()
{
	// 1. Define the Sweep geometry based on the GDD specs
	const FVector StartLocation = FirstPersonCameraComponent->GetComponentLocation();
	const FVector ForwardVector = FirstPersonCameraComponent->GetForwardVector();
	const FVector EndLocation = StartLocation + (ForwardVector * 250.f); // 250cm max reach
	const float SphereRadius = 15.f; // 15cm thick detection sphere

	FHitResult HitResult;
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this); // Ignore the player's own collision

	// 2. Perform the Sphere Sweep
	bool bHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		FQuat::Identity,
		ECC_Visibility, // Trace against anything visible
		FCollisionShape::MakeSphere(SphereRadius),
		TraceParams
	);

	// 3. Process the Hit
	if (bHit && HitResult.GetActor())
	{
		// Try to cast the hit actor to our Interface
		IWCOInteractable* HitInteractable = Cast<IWCOInteractable>(HitResult.GetActor());

		if (HitInteractable) // Scenario A: We hit a valid bottle or crate
		{
			// If this is a NEW object we weren't looking at during the last frame
			if (HitInteractable != CurrentInteractable)
			{
				// 1. Turn off the outline on the old object (if there was one)
				if (CurrentInteractable)
				{
					CurrentInteractable->Unhighlight();
				}

				// 2. Turn on the outline for the new object
				HitInteractable->Highlight();

				// 3. Cache the pointer so the 'E' key knows what to pick up
				CurrentInteractable = HitInteractable;
			}
		}
		else // Scenario B: We hit a non-interactable object (like a wall or the wooden shelf)
		{
			if (CurrentInteractable)
			{
				CurrentInteractable->Unhighlight();
				CurrentInteractable = nullptr;
			}
		}
	}
	else // Scenario C: We hit absolutely nothing (looking into empty space)
	{
		if (CurrentInteractable)
		{
			CurrentInteractable->Unhighlight();
			CurrentInteractable = nullptr;
		}
	}
}
