// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WineCellar/Character/WCOSkillTypes.h"
#include "WCOSkillComponent.generated.h"

class UDataTable;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WINECELLAR_API UWCOSkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UWCOSkillComponent();

	// The actual CSV Data Table asset assigned in the Blueprint Editor
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skills")
	UDataTable* SkillDatabase;
	
	// Tracks the current level of unlocked skills (Key: RowName, Value: Current Level)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skills")
	TMap<FName, int32> UnlockedSkills;

	// Universal fetch function for the rest of your game to use
	UFUNCTION(BlueprintCallable, Category = "Skills")
	float GetModifierValue(const ESkillModifierType ModType) const;
};