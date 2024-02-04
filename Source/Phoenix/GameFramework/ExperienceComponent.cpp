// Created by Bruce Crum.


#include "Phoenix/GameFramework/ExperienceComponent.h"

// Sets default values for this component's properties
UExperienceComponent::UExperienceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false; 
	SetComponentTickEnabled(false);

	ExperienceDataTable = nullptr;
	TotalExperience = 0;
	CurrentLevel = 1;
}

void UExperienceComponent::GainExperience(int32 ExperienceGained)
{
	// Not that we should be gaining negative experience, but never trust inputed data.
	if (ExperienceGained >= 1)
	{
		TotalExperience += ExperienceGained;
		BlueprintOnExperiencedGained(ExperienceGained);

		bool bHasLeveledUp = false;

		do // do-while loop to handle multiple level ups.
			if (const auto ExperienceData = ExperienceDataTable->FindRow<FExperienceData>(FName(*FString::FromInt(CurrentLevel + 1)), TEXT("")))
			{
				if (TotalExperience >= ExperienceData->ExperienceRequired)
				{
					bHasLeveledUp = true;
					++CurrentLevel;
					BlueprintOnLevelUp(CurrentLevel);
				}
			}
			else
			{
				bHasLeveledUp = false;
			}
		while (bHasLeveledUp);
	}
	else
	{
		// TODO: Should this be it's own log?
		UE_LOG(LogTemp, Warning, TEXT("%s (owner %s) gained negative experience, please investigate."), *GetName(), *GetOwner()->GetName());
	}
}