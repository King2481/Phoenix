// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Phoenix/UI/Widgets/Windows/DragableWindow.h"
#include "CharacterMenu.generated.h"

/**
 * 
 */
UCLASS()
class PHOENIX_API UCharacterMenu : public UDragableWindow
{
	GENERATED_BODY()

public:

	UCharacterMenu();

	// UUserWidget interface
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	// End of UUserWidget interface

protected:

	UFUNCTION()
	void OnCharacterMenuToggled();
	
};
