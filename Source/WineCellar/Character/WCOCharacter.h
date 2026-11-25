// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "WCOCharacter.generated.h"

class AWCOBottleBase;
class UCameraComponent;
class USceneComponent;
class UInputMappingContext;
class UInputAction;
class AActor;

UCLASS(config=Game)
class WINECELLAR_API AWCOCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	AWCOCharacter();
	
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact();

private:
	
	// -- Components --
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	// The spatial socket where grabbed bottles will attach
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	USceneComponent* HeldItemLocation;

	// -- Enhanced Input Assets --
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	// Pointer to the currently held bottle (nullptr if empty-handed)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction|State", meta = (AllowPrivateAccess = "true"))
	AWCOBottleBase* CurrentHeldBottle;
    
	// Configurable trace distance for grabbing/placing
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	float InteractionDistance = 250.0f;
};
