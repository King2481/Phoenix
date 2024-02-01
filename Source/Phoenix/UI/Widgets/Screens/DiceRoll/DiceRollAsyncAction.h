// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Engine/CancellableAsyncAction.h"
#include "Phoenix/GameFramework/PhoenixTypes.h"
#include "DiceRollAsyncAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDiceRollSignature);

class UDiceRollScreen;

/**
 * 
 */
UCLASS()
class PHOENIX_API UDiceRollAsyncAction : public UCancellableAsyncAction
{
	GENERATED_BODY()

public:

	UDiceRollAsyncAction();

	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", Category = "Dice Roll Async", WorldContext = "WorldContextObject"))
	static UDiceRollAsyncAction* DisplayDiceRollScreenAsync(UObject* WorldContextObject, APlayerController* ForPlayer, const FDiceRollScreenInfo& InDiceRollScreenInfo);

protected:

	UPROPERTY(BlueprintAssignable)
	FDiceRollSignature OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FDiceRollSignature OnFail;

	UPROPERTY(BlueprintAssignable)
	FDiceRollSignature OnClose;

	UPROPERTY(BlueprintAssignable)
	FDiceRollSignature OnCanceled;

	UPROPERTY()
	TObjectPtr<UDiceRollScreen> DiceRollScreenInstance;

	UFUNCTION()
	void OnDiceRollResult(bool bSuccess);

	UFUNCTION()
	void OnDiceRollCanceled();

	UFUNCTION()
	void OnScreenClose();

private:

	void CleanupAction();

	FDiceRollScreenInfo DiceRollScreenInfo;

	TObjectPtr<APlayerController> PlayerController;
};
