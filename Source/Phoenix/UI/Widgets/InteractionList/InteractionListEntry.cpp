// Created by Bruce Crum.


#include "Phoenix/UI/Widgets/InteractionList/InteractionListEntry.h"
#include "Phoenix/UI/Widgets/InteractionList/InteractionListEntryObject.h"
#include "Phoenix/GameFramework/Targeting/InteractionData.h"

#include "Components/TextBlock.h"

UInteractionListEntry::UInteractionListEntry(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    InteractionText = nullptr;
    InteractionObject = nullptr;
}

void UInteractionListEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
    InteractionObject = Cast<UInteractionListEntryObject>(ListItemObject);
    if (InteractionObject)
    {
        if (InteractionText)
        {
            InteractionText->SetText(InteractionObject->Interaction->LocalizedName);
        }
    }
}