// Created by Bruce Crum.


#include "Phoenix/GameFramework/FloatingText/FloatingTextNotification.h"
#include "Phoenix/GameFramework/FloatingText/FloatingTextEntity.h"
#include "Phoenix/GameFramework/Health/HealthComponent.h"
#include "Phoenix/Settings/UIDeveloperSettings.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UFloatingTextNotification::UFloatingTextNotification()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetComponentTickEnabled(false);

	FloatingTextWidgetPool = FUserWidgetPool();
}


// Called when the game starts
void UFloatingTextNotification::BeginPlay()
{
	Super::BeginPlay();

	FloatingTextWidgetPool.SetWorld(GetWorld());

	if (const auto HealthComponent = GetOwner()->GetComponentByClass<UHealthComponent>())
	{
		HealthComponent->OnHealthChangedDelegate.AddDynamic(this, &ThisClass::OnOwnersHealthChanged);
	}
}

void UFloatingTextNotification::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	FloatingTextWidgetPool.ReleaseAll(true);

	if (const auto HealthComponent = GetOwner()->GetComponentByClass<UHealthComponent>())
	{
		HealthComponent->OnHealthChangedDelegate.RemoveDynamic(this, &ThisClass::OnOwnersHealthChanged);
	}

	Super::EndPlay(EndPlayReason);
}

void UFloatingTextNotification::OnOwnersHealthChanged(const FHealthChangeResult& NewInfo)
{
	// TODO: This will need the be refactored as there may be things besides health changes that have floating text. But for the time being, this is fine.

	if (const auto UISettings = GetDefault<UUIDeveloperSettings>()) // Access via CDO
	{
		if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			for (FDamageInfo DamageInfo : NewInfo.DamageSources)
			{
				if (const auto Widget = FloatingTextWidgetPool.GetOrCreateInstance<UFloatingTextEntity>(UISettings->DefaultFloatingTextWidget.LoadSynchronous()))
				{
					FFloatingTextCreationInfo CreationInfo;
					CreationInfo.TextToDisplay = FText::FromString(FString::FromInt(DamageInfo.ChangeAmount));

					UGameplayStatics::ProjectWorldToScreen(PC, DamageInfo.HitLocation, CreationInfo.RenderLocation, false);

					Widget->SetFloatingTextInfo(CreationInfo);
				}
			}
		}
	}
}


