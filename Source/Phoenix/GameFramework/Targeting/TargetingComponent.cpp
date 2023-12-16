// Created by Bruce Crum.


#include "Phoenix/GameFramework/Targeting/TargetingComponent.h"
#include "Phoenix/GameFramework/Targeting/Targetable.h"
#include "Phoenix/Player/PhoenixPlayerController.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTargetingComponent::UTargetingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetComponentTickEnabled(false);

	// ...
}


// Called when the game starts
void UTargetingComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnBeginCursorOver.AddDynamic(this, &ThisClass::OnBeginCursorOver);
	GetOwner()->OnEndCursorOver.AddDynamic(this, &ThisClass::OnEndCursorOver);
}

void UTargetingComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetOwner()->OnBeginCursorOver.RemoveDynamic(this, &ThisClass::OnBeginCursorOver);
	GetOwner()->OnEndCursorOver.RemoveDynamic(this, &ThisClass::OnEndCursorOver);

	Super::EndPlay(EndPlayReason);
}

void UTargetingComponent::OnBeginCursorOver(AActor* TouchedActor)
{
	if (const auto PC = Cast<APhoenixPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		if (const auto Targetable = Cast<ITargetable>(GetOwner()))
		{
			// Inform player of target.
			FTargetableInfo TargetInfo = ITargetable::Execute_GetTargetInfo(GetOwner());

			const TArray<UInteractionData*> PossibleInteractions = ITargetable::Execute_GetPossibleInteractions(GetOwner());
			if (!PossibleInteractions.IsEmpty())
			{
				// Add any interactions. 
				TargetInfo.AddInteractions(PossibleInteractions);
			}

			PC->UpdateCurrentPlayerTargetInfo(TargetInfo);

			// Highlight Target
			const FMeshHighlightInfo MeshHighlightInfo = ITargetable::Execute_GetMeshHighlightInfo(GetOwner());
			if (MeshHighlightInfo.MeshToHighlight != nullptr)
			{
				MeshHighlightInfo.MeshToHighlight->SetOverlayMaterial(MeshHighlightInfo.MaterialToUse);
			}
		}
	}
}

void UTargetingComponent::OnEndCursorOver(AActor* TouchedActor)
{
	if (const auto PC = Cast<APhoenixPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		PC->UpdateCurrentPlayerTargetInfo(FTargetableInfo());

		const FMeshHighlightInfo MeshHighlightInfo = ITargetable::Execute_GetMeshHighlightInfo(GetOwner());
		if (MeshHighlightInfo.MeshToHighlight != nullptr)
		{
			MeshHighlightInfo.MeshToHighlight->SetOverlayMaterial(nullptr);
		}
	}
}