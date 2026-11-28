// Fill out your copyright notice in the Description page of Project Settings.

#include "WCOSkillComponent.h"

UWCOSkillComponent::UWCOSkillComponent()
{
	// You likely don't need this component to tick every frame, 
	// saving you some performance overhead!
	PrimaryComponentTick.bCanEverTick = false; 
}

float UWCOSkillComponent::GetModifierValue(const ESkillModifierType ModType) const
{
	float TotalModifier = 1.0f; // Default baseline is 100%

	if (!SkillDatabase)
	{
		UE_LOG(LogTemp, Error, TEXT("SkillComponent on %s has no SkillDatabase assigned!"), *GetOwner()->GetName());
		return TotalModifier;
	}

	for (const auto& SkillPair : UnlockedSkills)
	{
		// Look up the row in DT_SkillDatabase using the TMap Key
		if (const FSkillData* SkillData = SkillDatabase->FindRow<FSkillData>(SkillPair.Key, TEXT("SkillModifierLookup")))
		{
			if (SkillData->ModifierType == ModType)
			{
				// Add the cumulative boost based on the player's level in this skill
				TotalModifier += (SkillData->ValuePerLevel * SkillPair.Value);
			}
		}
	}
	
	return TotalModifier;
}
