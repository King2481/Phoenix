// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Engine/CancellableAsyncAction.h"
#include "PickpocketAsyncAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPickpocketSignature, EPickpocketResult, Result);

class UPickpocketScreen;
class UInventoryComponent;


/**
 * 
 */
UCLASS()
class PHOENIX_API UPickpocketAsyncAction : public UCancellableAsyncAction
{
	GENERATED_BODY()

public:

	UPickpocketAsyncAction();

	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", Category = "Pickpocket Async", WorldContext = "WorldContextObject"))
	static UPickpocketAsyncAction* DisplayPickpocketScreenAsync(UObject* WorldContextObject, APlayerController* ForPlayer, UInventoryComponent* PickpocketingFromInventory, UInventoryComponent* InPocketerInventory);

protected:

	UPROPERTY()
	TObjectPtr<UPickpocketScreen> PickpocketScreenInstance;

	UPROPERTY(BlueprintAssignable)
	FPickpocketSignature OnResultRecieved;

	UFUNCTION()
	void OnPickpocketResult(EPickpocketResult Result);

	UFUNCTION(BlueprintCallable, Category = "Pickpocket Async Action")
	void CleanupAction();

private:

	TObjectPtr<APlayerController> PlayerController;
	TObjectPtr<UInventoryComponent> TargetInventory;
	TObjectPtr<UInventoryComponent> PocketerInventory;
	
};
