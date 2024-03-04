// Created by Bruce Crum.


#include "Phoenix/UI/Widgets/HealthBar.h"
#include "Phoenix/GameFramework/Health/HealthComponent.h"

#include "Components/ProgressBar.h"
#include "Components/RichTextBlock.h"
#include "Blueprint/WidgetTree.h"

UHealthBar::UHealthBar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	HealthBar = nullptr;
	HealthText = nullptr;

	TrackedHealthComponent = nullptr;
	bInverselyFill = false;
}

void UHealthBar::NativeDestruct()
{
	ClearTrackingBindings();

	Super::NativeDestruct();
}

void UHealthBar::SetTrackingHealthComponent(UHealthComponent* NewTrackedHealth)
{
	ClearTrackingBindings();

	if (NewTrackedHealth)
	{
		TrackedHealthComponent = NewTrackedHealth;
		TrackedHealthComponent->OnHealthChangedDelegate.AddDynamic(this, &ThisClass::OnTrackingHealthChanged);

		UpdateHealthBar();
	}
}

void UHealthBar::ClearTrackingBindings()
{
	if (TrackedHealthComponent)
	{
		TrackedHealthComponent->OnHealthChangedDelegate.RemoveDynamic(this, &ThisClass::OnTrackingHealthChanged);
	}
}

void UHealthBar::OnTrackingHealthChanged(const FHealthChangeResult& NewInfo)
{
	UpdateHealthBar();
}

void UHealthBar::UpdateHealthBar()
{
	if (TrackedHealthComponent)
	{
		if (HealthBar)
		{
			float HealthAsRatio = TrackedHealthComponent->GetHealthRemainingAsRatio();
			HealthAsRatio = bInverselyFill ? 1.0f - HealthAsRatio : HealthAsRatio;
			HealthBar->SetPercent(HealthAsRatio);
		}

		if (HealthText)
		{
			FText FormatedHealthText = FText::GetEmpty();

			for (const FHealthTypeEntry& Entry : TrackedHealthComponent->GetHealthTypeEntries())
			{
				FFormatNamedArguments Arguments;
				Arguments.Add(TEXT("CurrentString"), FormatedHealthText);
				Arguments.Add(TEXT("CurrentHealth"), Entry.Amount);
				Arguments.Add(TEXT("MaxHealth"), Entry.MaxAmount);

				if (Entry.HealthType->TextColor.IsEmpty())
				{
					FormatedHealthText = FText::Format(NSLOCTEXT("TextDisplayNamespace", "HealthFormatText", "{CurrentString} {CurrentHealth}/{MaxHealth}"), Arguments);
				}
				else
				{
					Arguments.Add(TEXT("Color"), FText::FromString(Entry.HealthType->TextColor));
					FormatedHealthText = FText::Format(NSLOCTEXT("TextDisplayNamespace", "HealthFormatTextColor", "{CurrentString} <{Color}>{CurrentHealth}/{MaxHealth}</>"), Arguments);
				}
			}
			
			HealthText->SetText(FormatedHealthText);
		}
	}
}