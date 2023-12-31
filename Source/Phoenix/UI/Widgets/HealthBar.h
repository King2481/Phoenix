// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBar.generated.h"

class UProgressBar;
class UTextBlock;
class UHealthComponent;
struct FHealthChangeInfo;

/**
 * 
 */
UCLASS()
class PHOENIX_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:

	UHealthBar(const FObjectInitializer& ObjectInitializer);

	// UUserWidget interface
	virtual void NativeDestruct() override;
	// End of UUserWidget interface

	UFUNCTION(BlueprintCallable, Category = "Health Bar")
	void SetTrackingHealthComponent(UHealthComponent* NewTrackedHealth);

	void ClearTrackingBindings();
	
protected:

	UPROPERTY(BlueprintReadOnly, Category = "Health Bar", meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;

	UPROPERTY(BlueprintReadOnly, Category = "Health Bar", meta = (BindWidget))
	TObjectPtr<UTextBlock> HealthText;

	UPROPERTY(BlueprintReadOnly, Category = "Health Bar")
	TObjectPtr<UHealthComponent> TrackedHealthComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Health Bar")
	bool bInverselyFill;

	UFUNCTION()
	void OnTrackingHealthChanged(const FHealthChangeResult& NewInfo);

private:

	void UpdateHealthBar();

};
