// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ExplosionComponent.generated.h"

class UExplosionData;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHOENIX_API UExplosionComponent : public USceneComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UExplosionComponent();

	UFUNCTION(BlueprintCallable, Category = "Explosion Component")
	void Explode(APawn* Instigator = nullptr, UExplosionData* ExplosionOverride = nullptr);

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Explosion Component")
	TObjectPtr<UExplosionData> DefaultExplosionData;

	
};
