// Created by Bruce Crum.


#include "Phoenix/UI/Widgets/InteractionList/InteractionListEntryObject.h"

UInteractionListEntryObject::UInteractionListEntryObject()
{
	Interaction = nullptr;
	Target = nullptr;
}

void UInteractionListEntryObject::Init(UInteractionData* InInteraction, UPhoenixAbilitySystemComponent* InTarget)
{
	Interaction = InInteraction;
	Target = InTarget;
}
