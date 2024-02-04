// Created by Bruce Crum.


#include "Phoenix/Characters/PhoenixCharacter.h"
#include "Phoenix/Items/InventoryComponent.h"
#include "Phoenix/Abilities/PhoenixAbilitySystemComponent.h"
#include "Phoenix/Abilities/PhoenixGameplayAbility.h"
#include "Phoenix/GameModes/PhoenixGameModeBase.h"
#include "Phoenix/GameFramework/Health/HealthComponent.h"
#include "Phoenix/GameFramework/NameComponent.h"

#include "Components/CapsuleComponent.h"

// Sets default values
APhoenixCharacter::APhoenixCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	AbilitySystemComponent = CreateDefaultSubobject<UPhoenixAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	NameComponent = CreateDefaultSubobject<UNameComponent>(TEXT("NameComponent"));
	TargetingComponent = CreateDefaultSubobject<UTargetingComponent>(TEXT("TargetingComponent"));
	ReputationComponent = CreateDefaultSubobject<UReputationComponent>(TEXT("ReputationComponent"));
	CombatFloatyNotification = CreateDefaultSubobject<UCombatFloatyNotification>(TEXT("CombatFloatyNotification"));

	SneakAbility = nullptr;
}

// Called when the game starts or when spawned
void APhoenixCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	AbilitySystemComponent->GivePhoenixAbility(SneakAbility);

	HealthComponent->OnDeathDelegate.AddDynamic(this, &ThisClass::OnDeathEvent);
}

void APhoenixCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	HealthComponent->OnDeathDelegate.RemoveDynamic(this, &ThisClass::OnDeathEvent);

	Super::EndPlay(EndPlayReason);
}

// Called every frame
void APhoenixCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APhoenixCharacter::OnSneakActivated()
{
	if (SneakAbility)
	{
		AbilitySystemComponent->TryActivateAbilityByClass(SneakAbility);
	}
	else
	{
		// TODO: Log
	}
}

void APhoenixCharacter::OnDeathEvent(const FOnDeathInfo& DeathInfo)
{
	if (const auto GM = GetWorld()->GetAuthGameMode<APhoenixGameModeBase>())
	{
		GM->OnEntityKilled(this, DeathInfo.KillerABS);
	}

	OnDeath();
}

void APhoenixCharacter::OnDeath()
{
	// DetachFromControllerPendingDestroy();

	// Only set the life span if they have nothing to loot.
	if (InventoryComponent->GetInventoryItems().IsEmpty())
	{
		SetLifeSpan(60.0f);
	}

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionProfileName("Ragdoll");
	GetMesh()->SetSimulatePhysics(true);
	BlueprintOnDeath();
}

FTargetableInfo APhoenixCharacter::GetTargetInfo_Implementation() const
{
	return FTargetableInfo(HealthComponent, AbilitySystemComponent, TargetingComponent, NameComponent->GetEntityName());
}