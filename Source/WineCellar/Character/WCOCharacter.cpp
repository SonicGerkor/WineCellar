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
		
		// Jump
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
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
	if (CurrentHeldBottle)
	{
		PlaceItem();
	}
	else
	{
		GrabItem();
	}
}

void AWCOCharacter::GrabItem()
{
	const FVector Start = FirstPersonCameraComponent->GetComponentLocation();
	const FVector End = Start + (FirstPersonCameraComponent->GetForwardVector() * InteractionDistance);
	
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	const FCollisionShape SphereShape = FCollisionShape::MakeSphere(15.0f);

	const bool bHit = GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECC_Visibility, SphereShape, QueryParams);

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

void AWCOCharacter::PlaceItem()
{
	const FVector Start = FirstPersonCameraComponent->GetComponentLocation();
	const FVector End = Start + (FirstPersonCameraComponent->GetForwardVector() * InteractionDistance);
	
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(CurrentHeldBottle);

	const FCollisionShape SphereShape = FCollisionShape::MakeSphere(15.0f);

	const bool bHit = GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECC_Visibility, SphereShape, QueryParams);

	if (bHit)
	{
		if (AActor* HitActor = HitResult.GetActor())
		{
		    TArray<UWCOSlotComponent*> ShelfSlots;
		    HitActor->GetComponents<UWCOSlotComponent>(ShelfSlots);

		    UWCOSlotComponent* ClosestSlot = nullptr;
		    float ClosestDistSq = MAX_flt;

		    // DEBUG: Draw a RED sphere exactly where your crosshair hit the physical wood
		    DrawDebugSphere(GetWorld(), HitResult.Location, 5.f, 12, FColor::Red, false, 2.f);

		    for (UWCOSlotComponent* Slot : ShelfSlots)
		    {
		        if (Slot && !Slot->bIsOccupied) 
		        {
		            float DistSq = FVector::DistSquared(HitResult.Location, Slot->GetComponentLocation());
		            float ActualDistance = FMath::Sqrt(DistSq); // Convert squared to actual units (cm)
		            
		            // DEBUG: Draw a BLUE sphere at the slot's actual coordinate
		            DrawDebugSphere(GetWorld(), Slot->GetComponentLocation(), 5.f, 12, FColor::Blue, false, 2.f);
		            
		            // DEBUG: Draw a GREEN line connecting your hit point to the slot
		            DrawDebugLine(GetWorld(), HitResult.Location, Slot->GetComponentLocation(), FColor::Green, false, 2.f);
		            
		            // DEBUG: Print the exact distance to the screen
		            GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, 
		                FString::Printf(TEXT("Slot %s is %f cm away"), *Slot->GetName(), ActualDistance));

		            // I bumped the threshold to 2500.f (50cm) just to see if distance was the issue!
		            if (DistSq < ClosestDistSq && DistSq < 2500.f) 
		            {
		                ClosestDistSq = DistSq;
		                ClosestSlot = Slot;
		            }
		        }
		    }

		    if (ClosestSlot)
		    {
		        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, 
		            FString::Printf(TEXT("SUCCESS: Snapping to %s!"), *ClosestSlot->GetName()));
		            
		    	CurrentHeldBottle->AttachToComponent(ClosestSlot, FAttachmentTransformRules::KeepRelativeTransform);

		    	// Shift the bottle forward so its center rests in the slot
		    	// (Assuming the bottle is ~30cm tall, we shift it by 15cm)
		    	CurrentHeldBottle->SetActorRelativeLocation(FVector(0.f, 0.f, -20.f));
		        ClosestSlot->bIsOccupied = true;
		        CurrentHeldBottle = nullptr; 
		    }
		    else
		    {
		        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("FAILED: No slot was close enough to the hit location!"));
		    }
		}
	}
}
