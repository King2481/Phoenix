// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilityTypes.h"
#include "PhoenixAbilitySystemComponent.generated.h"

class UPhoenixGameplayAbility;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangeHealthInfoDelegate, const FModifyHealthInfo&, NewModifyInfo);

/**
 * 
 */
UCLASS()
class PHOENIX_API UPhoenixAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	UPhoenixAbilitySystemComponent();

	UFUNCTION(BlueprintCallable, Category = "Phoenix Ability System")
	void GivePhoenixAbility(TSubclassOf<UPhoenixGameplayAbility> Ability);
	
	UFUNCTION(BlueprintCallable, Category = "Phoenix Ability System")
	void ClearPhoenixAbility(TSubclassOf<UPhoenixGameplayAbility> Ability);

	UFUNCTION(BlueprintCallable, Category = "Phoenix Ability System")
	void ModifyHealth(const FModifyHealthInfo& ModifyHealthInfo);

	UFUNCTION(BlueprintCallable, Category = "Phoenix Ability System")
	void SetTargetDataAndTryAbility(const FTargetData& InTargetData, TSubclassOf<UPhoenixGameplayAbility> Ability);

	UPROPERTY(BlueprintAssignable)
	FChangeHealthInfoDelegate ChangeHealthInfoDelegate;

	UFUNCTION(BlueprintCallable, Category = "Phoenix Ability System")
	FTargetData GetCurrentTargetData() const { return CurrentTargetData; }

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Phoenix Ability System")
	FTargetData CurrentTargetData;

};
