// Created by Bruce Crum.


#include "Phoenix/UI/Widgets/HealthBar.h"
#include "Phoenix/GameFramework/Health/HealthComponent.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"

UHealthBar::UHealthBar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
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
			int32 AccumulativeHealth = 0;

			for (const FHealthTypeEntry& Entry : TrackedHealthComponent->GetHealthTypeEntries())
			{
				AccumulativeHealth += Entry.Amount;
			}

			// TODO: Sequence to account for multiple health pools.
			HealthText->SetText(FText::FromString(FString::FromInt(AccumulativeHealth)));
		}
	}
}