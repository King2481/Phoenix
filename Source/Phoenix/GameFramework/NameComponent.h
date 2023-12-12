// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NameComponent.generated.h"

USTRUCT(BlueprintType)
struct FTextAppendix
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UObject> Context;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Text;

	FTextAppendix()
	{
		Context = nullptr;
		Text = FText::GetEmpty();
	}

	FTextAppendix(UObject* InContext, const FText& InText)
	{
		Context = InContext;
		Text = InText;
	}

	bool operator==(const FTextAppendix& Other) const
	{
		return Context == Other.Context;
	}

	explicit operator bool() const
	{
		return Context != nullptr;
	}
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHOENIX_API UNameComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UNameComponent();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure, Category = "Name Component")
	FText GetEntityName() const { return EntityName; }

	UFUNCTION(BlueprintPure, Category = "Name Component")
	FText GetDisplayName() const { return DisplayName; }

	UFUNCTION(BlueprintCallable, Category = "Name Component")
	void SetEntityName(const FText& InName);

	UFUNCTION(BlueprintCallable, Category = "Name Component")
	void AddToTextAppendix(const FTextAppendix& InAppendix);

	UFUNCTION(BlueprintCallable, Category = "Name Component")
	void RemoveFromAppendix(UObject* SourceObject);

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Name Component")
	FText EntityName;

	UPROPERTY(BlueprintReadOnly, Category = "Name Component")
	FText DisplayName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Name Component")
	TArray<FTextAppendix> CurrentAppendixes;

private:

	void RebuildDisplayName();
		
};
