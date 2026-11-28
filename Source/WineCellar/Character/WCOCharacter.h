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
class IWCOInteractable;
class UWCOSkillComponent;

UCLASS(config=Game)
class WINECELLAR_API AWCOCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	AWCOCharacter();
	
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaSeconds) override;
	
	FORCEINLINE AWCOBottleBase* GetHeldBottle() const { return HeldBottle; }
	FORCEINLINE void SetHeldBottle(AWCOBottleBase* InHeldBottle) { HeldBottle = InHeldBottle; }
	
	FORCEINLINE UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	
	FORCEINLINE UWCOSkillComponent* GetSkillComponent() const { return SkillComponent; }

protected:
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact();
	
	IWCOInteractable* CurrentInteractable = nullptr;

private:
	
	void PerformInteractionTrace();
	
	// -- Components --
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	// The spatial socket where grabbed bottles will attach
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	USceneComponent* HeldItemLocation;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skills", meta = (AllowPrivateAccess = "true"))
	UWCOSkillComponent* SkillComponent;

	// -- Enhanced Input Assets --
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	// Pointer to the currently held bottle (nullptr if empty-handed)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction|State", meta = (AllowPrivateAccess = "true"))
	AWCOBottleBase* HeldBottle;
    
	// Configurable trace distance for grabbing/placing
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	float InteractionDistance = 250.0f;
};
