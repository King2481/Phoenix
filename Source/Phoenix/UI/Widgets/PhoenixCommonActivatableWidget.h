// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Misc/Optional.h"
#include "PhoenixCommonActivatableWidget.generated.h"

/**
 * 
 */
UCLASS()
class PHOENIX_API UPhoenixCommonActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:

	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override
	{
		return FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::NoCapture, false);
	}
	
};
