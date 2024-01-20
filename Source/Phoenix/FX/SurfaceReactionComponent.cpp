// Created by Bruce Crum.


#include "Phoenix/FX/SurfaceReactionComponent.h"
#include "Phoenix/FX/SurfaceReactionData.h"

#include "Kismet/GameplayStatics.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values for this component's properties
USurfaceReactionComponent::USurfaceReactionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetComponentTickEnabled(false);

	DefaultSurfaceReactionData = nullptr;
}

void USurfaceReactionComponent::PlaySurfaceReactionFromHitResult(const FHitResult& InHitResult, USurfaceReactionData* DataOverride /*= nullptr */)
{
	const USurfaceReactionData* ChosenData = DataOverride ? DataOverride : DefaultSurfaceReactionData;

	if (InHitResult.PhysMaterial.Get())
	{
		if (FPhysicalSurfaceReactionData SurfaceReaction = ChosenData->SurfaceToReactionDataMap.FindRef(InHitResult.PhysMaterial.Get()->SurfaceType))
		{
			if (SurfaceReaction.ReactionSound)
			{
				UGameplayStatics::PlaySoundAtLocation(GetOwner(), SurfaceReaction.ReactionSound, InHitResult.ImpactPoint);
			}

			if (SurfaceReaction.ReactionFX)
			{
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetOwner(), SurfaceReaction.ReactionFX, InHitResult.ImpactPoint, InHitResult.ImpactNormal.Rotation());
			}
		}
	}
}