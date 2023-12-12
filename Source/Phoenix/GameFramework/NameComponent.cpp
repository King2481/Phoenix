// Created by Bruce Crum.


#include "Phoenix/GameFramework/NameComponent.h"

// Sets default values for this component's properties
UNameComponent::UNameComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetComponentTickEnabled(false);

	EntityName = FText::GetEmpty();
	DisplayName = FText::GetEmpty();
}

void UNameComponent::BeginPlay()
{
	Super::BeginPlay();

	RebuildDisplayName();
}

void UNameComponent::SetEntityName(const FText& InName)
{
	EntityName = InName;
	RebuildDisplayName();
}

void UNameComponent::AddToTextAppendix(const FTextAppendix& InAppendix)
{
	const int32 ExistingIndex = CurrentAppendixes.IndexOfByPredicate([InAppendix](const FTextAppendix& ExistingAppendix) {
		return ExistingAppendix.Context == InAppendix.Context;
		});

	if (ExistingIndex != INDEX_NONE)
	{
		CurrentAppendixes[ExistingIndex] = InAppendix;
	}
	else
	{
		CurrentAppendixes.AddUnique(InAppendix);
	}

	RebuildDisplayName();
}

void UNameComponent::RemoveFromAppendix(UObject* SourceContext)
{
	CurrentAppendixes.RemoveAll([SourceContext](const FTextAppendix& Appendix) {
		return Appendix.Context == SourceContext;
		});

	RebuildDisplayName();
}

void UNameComponent::RebuildDisplayName()
{
	FText FormatedAppendixes = FText::GetEmpty();

	for (const FTextAppendix& Appendix : CurrentAppendixes)
	{
		FFormatNamedArguments AppendixArguments;
		AppendixArguments.Add(TEXT("Current"), FormatedAppendixes);
		AppendixArguments.Add(TEXT("AddedAppendix"), Appendix.Text);

		FormatedAppendixes = FText::Format(NSLOCTEXT("TextDisplayNamespace", "DisplayAppendixesFormatText", "{Current} ({AddedAppendix})"), AppendixArguments);
	}

	FFormatNamedArguments Arguments;
	Arguments.Add(TEXT("EntityName"), EntityName);
	Arguments.Add(TEXT("Appendixes"), FormatedAppendixes);

	DisplayName = FText::Format(NSLOCTEXT("TextDisplayNamespace", "DisplayNameFormatText", "{EntityName} {Appendixes}"), Arguments);
}