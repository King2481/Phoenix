// Created by Bruce Crum.


#include "Phoenix/GameFramework/CombatFloaties/CombatFloatyNotification.h"
#include "Phoenix/GameFramework/CombatFloaties/CombatFloatyEntity.h"
#include "Phoenix/GameFramework/Health/HealthComponent.h"
#include "Phoenix/Settings/UIDeveloperSettings.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCombatFloatyNotification::UCombatFloatyNotification()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetComponentTickEnabled(false);

	CombatFloatyWidgetPool = FUserWidgetPool();
}


// Called when the game starts
void UCombatFloatyNotification::BeginPlay()
{
	Super::BeginPlay();

	CombatFloatyWidgetPool.SetWorld(GetWorld());

	if (const auto HealthComponent = GetOwner()->GetComponentByClass<UHealthComponent>())
	{
		HealthComponent->OnHealthChangedDelegate.AddDynamic(this, &ThisClass::OnOwnersHealthChanged);
	}
}

void UCombatFloatyNotification::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CombatFloatyWidgetPool.ReleaseAll(true);

	if (const auto HealthComponent = GetOwner()->GetComponentByClass<UHealthComponent>())
	{
		HealthComponent->OnHealthChangedDelegate.RemoveDynamic(this, &ThisClass::OnOwnersHealthChanged);
	}

	Super::EndPlay(EndPlayReason);
}

void UCombatFloatyNotification::OnOwnersHealthChanged(const FHealthChangeResult& NewInfo)
{
	if (const auto UISettings = GetDefault<UUIDeveloperSettings>()) // Access via CDO
	{
		if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			for (FDamageInfo DamageInfo : NewInfo.DamageSources)
			{
				// TODO: Will need to release this widget when the animation is done
				if (const auto Widget = CombatFloatyWidgetPool.GetOrCreateInstance<UCombatFloatyEntity>(UISettings->DefaultFloatingTextWidget.LoadSynchronous()))
				{					
					FString FormatedString = FString::FromInt(DamageInfo.ChangeAmount);
					if (DamageInfo.bWasCrit)
					{
						// In Final Fantasy 14, crits are denoted with a !.
						FormatedString += FString("!");
					}

					FCombatFloatyCreationInfo CreationInfo;
					CreationInfo.TextToDisplay = FText::FromString(FormatedString);

					UGameplayStatics::ProjectWorldToScreen(PC, DamageInfo.HitLocation, CreationInfo.RenderLocation, false);

					Widget->SetCombatFloatyInfo(CreationInfo);
				}
			}
		}
	}
}

