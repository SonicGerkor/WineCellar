// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WCOSkillTypes.generated.h"

UENUM(BlueprintType)
enum class ESkillModifierType : uint8
{
	MovementSpeed,
	CarryCapacity,
	InspectionSpeed,
	HighlightRadius,
	BreakageResistance
};

USTRUCT(BlueprintType)
struct FSkillData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SkillName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsActiveSkill = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxLevel = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillModifierType ModifierType = ESkillModifierType::MovementSpeed;

	// e.g., Base value of 1.0. At level 1 it adds 0.25 (25% boost).
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ValuePerLevel = 0.25f; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BaseXPCost = 100;
};
