// Created by Bruce Crum.


#include "Phoenix/GameFramework/Perception/PerceptionCheckTrigger.h"
#include "Phoenix/GameFramework/PhoenixGameplayStatics.h"

// Base Begin

UPerceptionCheckTriggerBase::UPerceptionCheckTriggerBase()
{
	DifficultyClassToPercieve = 10;
	PerceptionCheckResponse = nullptr;
}

void UPerceptionCheckTriggerBase::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnTriggerOverlap);
}

void UPerceptionCheckTriggerBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::OnTriggerOverlap);

	Super::EndPlay(EndPlayReason);
}

void UPerceptionCheckTriggerBase::OnTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	HandleOverlapedActor(OtherActor);
}

void UPerceptionCheckTriggerBase::HandleOverlapedActor(AActor* OverlappedActor)
{
	const FDiceRollToBeatResult Result = UPhoenixGameplayStatics::RollDiceToBeat({ FDiceRollInfo(EDiceType::D20) }, DifficultyClassToPercieve);

	if (Result.bSuccessfullyPassed)
	{
		OnPercievedSuccess(OverlappedActor);
	}
}

void UPerceptionCheckTriggerBase::OnPercievedSuccess(AActor* Perciever)
{

}

// Base End

// Highlight Parent Begin

UPerceptionCheckTriggerHighlightParent::UPerceptionCheckTriggerHighlightParent()
{
	bHiddenUntilPercieved = false;
}

void UPerceptionCheckTriggerHighlightParent::BeginPlay()
{
	Super::BeginPlay();

	if (bHiddenUntilPercieved)
	{
		GetAttachParent()->SetVisibility(false);
	}
}

void UPerceptionCheckTriggerHighlightParent::OnPercievedSuccess(AActor* Perciever)
{
	Super::OnPercievedSuccess(Perciever);

	if (bHiddenUntilPercieved && !GetAttachParent()->IsVisible())
	{
		GetAttachParent()->SetVisibility(true);
	}
}

// Highlight Parent End

// Perception Check Response Begin

UPerceptionCheckResponse::UPerceptionCheckResponse()
{
	bHighlightParent = true; // In most cases.
	HighlightMaterial = nullptr;
}

// Perception Check Response End
