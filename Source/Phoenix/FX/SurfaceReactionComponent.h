// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SurfaceReactionComponent.generated.h"

class USurfaceReactionData;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHOENIX_API USurfaceReactionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USurfaceReactionComponent();

	UFUNCTION(BlueprintCallable, Category = "Surface Reaction Component")
	void PlaySurfaceReactionFromHitResult(const FHitResult& InHitResult, USurfaceReactionData* DataOverride = nullptr);

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Surface Reaction Component")
	TObjectPtr<USurfaceReactionData> DefaultSurfaceReactionData;

};
