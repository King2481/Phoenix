// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Phoenix/GameFramework/Targeting/TargetingTypes.h" // FTargetableInfo
#include "PhoenixPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class UNiagaraSystem;
class UPartyManagement;
class UMouseIconSet;
class UMouseWidget;
class UInteractionData;
class UPhoenixAbilitySystemComponent;
struct FInputActionValue;
struct FInventoryItem;

UENUM(BlueprintType)
enum class EInputMode : uint8
{
	Game        UMETA(DisplayName = "Game"),
	UI          UMETA(DisplayName = "UI"),
	GameAndUI   UMETA(DisplayName = "GameAndUI")
};

USTRUCT(BlueprintType)
struct FPlayerInteractionsInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FVector2D RenderLocation;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UPhoenixAbilitySystemComponent> Target;

	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<UInteractionData>> PossibleInteractions; // TODO: This needs to be a struct so that way we know what actions are considered illegal.

	FPlayerInteractionsInfo()
	{
		Target = nullptr;
		RenderLocation = FVector2D::ZeroVector;
	}

	FPlayerInteractionsInfo(const FVector2D& InRenderLocation, UPhoenixAbilitySystemComponent* InTarget, TArray<UInteractionData*> InPossibleInteractions)
	{
		RenderLocation = InRenderLocation;
		Target = InTarget;
		PossibleInteractions.Append(InPossibleInteractions);
	}
};

USTRUCT(BlueprintType)
struct FLootInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FVector2D RenderLocation;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UInventoryComponent> Inventory;

	FLootInfo()
	{
		RenderLocation = FVector2D::ZeroVector;
		Inventory = nullptr;
	}

	FLootInfo(const FVector2D& InRenderLocation, UInventoryComponent* InInventory)
	{
		RenderLocation = InRenderLocation;
		Inventory = InInventory;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerTargetChangedDelegate, const FTargetableInfo&, NewInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDisplayAllInteractionsDelegate, const FPlayerInteractionsInfo&, NewInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDisplayLootWindowDelegate, const FLootInfo&, NewInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectPressedDelegate, bool, bIsDown);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterMenuSelectedDelegate);

/**
 * 
 */
UCLASS()
class PHOENIX_API APhoenixPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	APhoenixPlayerController();

	virtual void SetupInputComponent() override;

	// Called when the actor begins play.
	virtual void BeginPlay() override;

	// Updates the players input mode, we may want different input modes such as Game / UI / Game & UI
	UFUNCTION(BlueprintCallable, Category = "Phoenix Player Controller")
	void UpdateInputMode(const EInputMode NewInputMode);

	UFUNCTION(BlueprintCallable, Category = "Phoenix Player Controller")
	void SpawnLootWindowAtLocation(const FVector& Location, UInventoryComponent* InInventory);

	UFUNCTION(BlueprintCallable, Category = "Phoenix Player Controller")
	void UpdateCurrentPlayerTargetInfo(const FTargetableInfo& NewTargetInfo);

	void OnClickedCurrentTarget();
	void DisplayAllPossibleInteractionForCurrentTarget();

	UPROPERTY(BlueprintAssignable)
	FOnPlayerTargetChangedDelegate OnPlayerTargetChangedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnDisplayAllInteractionsDelegate OnDisplayAllInteractionsDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnDisplayLootWindowDelegate OnDisplayLootWindowDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnSelectPressedDelegate OnSelectPressedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnCharacterMenuSelectedDelegate OnCharacterMenuSelectedDelegate;

	UFUNCTION(BlueprintPure, Category = "Phoenix Player Controller")
	UPartyManagement* GetPartyManagement() const { return PartyManagement; }

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Phoenix Player Controller")
	FTargetableInfo CurrentTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Phoenix Player Controller")
	TObjectPtr<UPartyManagement> PartyManagement;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Input")
	TObjectPtr<UNiagaraSystem> FXCursor;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Input")
	TArray<TObjectPtr<UInputMappingContext>> DefaultPlayerControls;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> SelectAction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> AltSelectAction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveCameraAction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> TurnCameraAction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> ZoomCameraAction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> SneakAction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> ToggleGroupSneakAction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> ToggleGroupMoveAction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveCharacterAction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> ShowInteractablesAction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> ShowCharacterMenuAction;

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	float ShortPressThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	float DisableFreeCamModeThreshold;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Phoenix Player Controller")
	TSubclassOf<UMouseWidget> MouseWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "Phoenix Player Controller")
	TObjectPtr<UMouseWidget> MouseWidgetInstance;

	void OnSelectStarted();
	void OnSelectTriggered();
	void OnSelectReleased();
	void OnAltSelectStarted();

	void OnMoveCameraTriggered(const FInputActionValue& Value);
	void OnMoveCameraReleased();

	void OnTurnCameraTriggered(const FInputActionValue& Value);
	void OnZoomCameraTriggered(const FInputActionValue& Value);

	void OnSneakStarted();
	void OnGroupSneakStarted();
	void OnToggleGroupMoveStarted();
	void OnShowInteractablesStarted();
	void OnShowInteractablesReleased();
	void OnShowCharacterMenuStarted();

	void OnMoveCharacterTriggered(const FInputActionValue& Value);

private:

	FVector CachedDestination;

	float FollowTime; // For how long it has been pressed

	bool bInGroupFollowMode;
	bool bClickedTargetableThisClick;
	
};
