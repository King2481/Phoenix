// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PhoenixHUD.generated.h"

USTRUCT(BlueprintType)
struct FWidgetCreationInfo
{
	GENERATED_BODY()

	/* The Widget class we are trying to create. */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<UUserWidget> WidgetClass;

	/* The widgets specified Z-Order. */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 ZOrder;

	FWidgetCreationInfo()
	{
		WidgetClass = nullptr;
		ZOrder = 0;
	}
};

/**
 * 
 */
UCLASS()
class PHOENIX_API APhoenixHUD : public AHUD
{
	GENERATED_BODY()

public:

	APhoenixHUD();

	/* Called when the actor begins play. */
	virtual void BeginPlay() override;

	// Called when the actor ends play.
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:

	/* What widgets are created for this HUD? */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Phoenix HUD")
	TArray<FWidgetCreationInfo> WidgetsToCreate;

	/* An array of instanced widgets this HUD has. */
	UPROPERTY()
	TArray<TObjectPtr<UUserWidget>> InstancedWidgets;
	
};
