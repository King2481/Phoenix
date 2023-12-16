// Created by Bruce Crum.


#include "Phoenix/Player/PhoenixPlayerController.h"
#include "Phoenix/Player/PhoenixPlayerCameraManager.h"
#include "Phoenix/Player/PartyManagement.h"
#include "Phoenix/Player/MouseWidget.h"
#include "Phoenix/Characters/PhoenixCharacter.h"
#include "Phoenix/Abilities/PhoenixAbilitySystemComponent.h"
#include "Phoenix/GameFramework/Targeting/InteractionData.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Blueprint/UserWidget.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/Character.h"

APhoenixPlayerController::APhoenixPlayerController()
{
	PartyManagement = CreateDefaultSubobject<UPartyManagement>(TEXT("Party Management"));

	bShowMouseCursor = true;
	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;
	DefaultMouseCursor = EMouseCursor::Default;
	MouseWidgetClass = nullptr;
	MouseWidgetInstance = nullptr;

	FXCursor = nullptr;
	SelectAction = nullptr;
	MoveCameraAction = nullptr;
	TurnCameraAction = nullptr;
	ZoomCameraAction = nullptr;
	SneakAction = nullptr;
	ToggleGroupSneakAction = nullptr;
	ToggleGroupMoveAction = nullptr;
	MoveCharacterAction = nullptr;
	ShowInteractablesAction = nullptr;
	ShortPressThreshold = 0.2f;
	DisableFreeCamModeThreshold = 0.2f;

	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.0f;
	bInGroupFollowMode = true;
	bClickedTargetableThisClick = false;

	CurrentTarget = FTargetableInfo();
}

void APhoenixPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* PlayerControls : DefaultPlayerControls)
		{
			Subsystem->AddMappingContext(PlayerControls, 0);
		}
	}

	if (MouseWidgetClass)
	{
		if (MouseWidgetInstance = CreateWidget<UMouseWidget>(this, MouseWidgetClass))
		{
			SetMouseCursorWidget(EMouseCursor::Default, MouseWidgetInstance);
		}
	}
}

void APhoenixPlayerController::UpdateInputMode(const EInputMode NewInputMode)
{
	switch (NewInputMode)
	{
		case EInputMode::UI:
			SetInputMode(FInputModeUIOnly());
			break;

		case EInputMode::GameAndUI:
			SetInputMode(FInputModeGameAndUI().SetHideCursorDuringCapture(false));
			break;

		case EInputMode::Game:
		default:
			SetInputMode(FInputModeGameOnly());
			break;
	}
}

void APhoenixPlayerController::UpdateCurrentPlayerTargetInfo(const FTargetableInfo& NewTargetInfo)
{
	CurrentTarget = NewTargetInfo;
	OnPlayerTargetChangedDelegate.Broadcast(CurrentTarget);
}

void APhoenixPlayerController::OnClickedCurrentTarget()
{
	if (UInteractionData* Data = CurrentTarget.PossibleInteractions[0].Get())
	{
		if (const auto ABS = GetPawn()->FindComponentByClass<UPhoenixAbilitySystemComponent>())
		{
			auto TargetDataHandle = FTargetData(CurrentTarget.ABSComponent);

			ABS->SetTargetDataAndTryAbility(TargetDataHandle, Data->InteractionAbility.LoadSynchronous());
		
			bClickedTargetableThisClick = true;
		}
	}
}

void APhoenixPlayerController::DisplayAllPossibleInteractionForCurrentTarget()
{
	float X, Y;
	GetMousePosition(X, Y);
	OnDisplayAllInteractionsDelegate.Broadcast(FPlayerInteractionsInfo(FVector2D(X, Y), CurrentTarget.ABSComponent, CurrentTarget.PossibleInteractions));
}

void APhoenixPlayerController::SpawnLootWindowAtLocation(const FVector& Location, UInventoryComponent* Inventory)
{
	FVector2D ScreenLocation;
	ProjectWorldLocationToScreen(Location, ScreenLocation);

	OnDisplayLootWindowDelegate.Broadcast(FLootInfo(ScreenLocation, Inventory));
}

void APhoenixPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings
	if (const auto EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Started, this, &ThisClass::OnSelectStarted);
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Triggered, this, &ThisClass::OnSelectTriggered);
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Completed, this, &ThisClass::OnSelectReleased);
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Canceled, this, &ThisClass::OnSelectReleased);

		// Setup move camera events
		EnhancedInputComponent->BindAction(MoveCameraAction, ETriggerEvent::Triggered, this, &ThisClass::OnMoveCameraTriggered);
		EnhancedInputComponent->BindAction(MoveCameraAction, ETriggerEvent::Canceled, this, &ThisClass::OnMoveCameraReleased);
		EnhancedInputComponent->BindAction(MoveCameraAction, ETriggerEvent::Completed, this, &ThisClass::OnMoveCameraReleased);
		EnhancedInputComponent->BindAction(TurnCameraAction, ETriggerEvent::Triggered, this, &ThisClass::OnTurnCameraTriggered);
		EnhancedInputComponent->BindAction(ZoomCameraAction, ETriggerEvent::Triggered, this, &ThisClass::OnZoomCameraTriggered);

		// Setup character events
		EnhancedInputComponent->BindAction(SneakAction, ETriggerEvent::Started, this, &ThisClass::OnSneakStarted);
		EnhancedInputComponent->BindAction(ToggleGroupSneakAction, ETriggerEvent::Started, this, &ThisClass::OnGroupSneakStarted);
		EnhancedInputComponent->BindAction(ToggleGroupMoveAction, ETriggerEvent::Started, this, &ThisClass::OnToggleGroupMoveStarted);
		EnhancedInputComponent->BindAction(MoveCharacterAction, ETriggerEvent::Triggered, this, &ThisClass::OnMoveCharacterTriggered);

		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Started, this, &ThisClass::OnShowInteractablesStarted);
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Completed, this, &ThisClass::OnShowInteractablesReleased);
	}
}

void APhoenixPlayerController::OnSelectStarted()
{
	StopMovement();
	OnSelectPressedDelegate.Broadcast(true);

	if (!CurrentTarget.PossibleInteractions.IsEmpty())
	{
		OnClickedCurrentTarget();
	}
}

// Triggered every frame when the input is held down
void APhoenixPlayerController::OnSelectTriggered()
{
	if (!bClickedTargetableThisClick)
	{
		// We flag that the input is being pressed
		FollowTime += GetWorld()->GetDeltaSeconds();

		if (FollowTime >= DisableFreeCamModeThreshold)
		{
			if (const auto PlayerCamera = Cast<APhoenixPlayerCameraManager>(PlayerCameraManager.Get()))
			{
				PlayerCamera->UpdateFreeCamStatus(false);
			}
		}

		// We look for the location in the world where the player has pressed the input
		FHitResult Hit;
		bool bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

		// If we hit a surface, cache the location
		if (bHitSuccessful)
		{
			CachedDestination = Hit.Location;
		}

		// Move towards mouse pointer or touch
		if (APawn* ControlledPawn = GetPawn())
		{
			FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
		}
	}
}

void APhoenixPlayerController::OnSelectReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold && !bClickedTargetableThisClick)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.0f;
	bClickedTargetableThisClick = false;

	OnSelectPressedDelegate.Broadcast(false);
}

void APhoenixPlayerController::OnMoveCameraTriggered(const FInputActionValue& Value)
{
	if (const auto PlayerCamera = Cast<APhoenixPlayerCameraManager>(PlayerCameraManager.Get()))
	{
		PlayerCamera->AddMoveInput(Value.Get<FVector2D>());
	}
}

void APhoenixPlayerController::OnMoveCameraReleased()
{
	if (const auto PlayerCamera = Cast<APhoenixPlayerCameraManager>(PlayerCameraManager.Get()))
	{
		PlayerCamera->AddMoveInput(FVector2D::ZeroVector);
	}
}

void APhoenixPlayerController::OnTurnCameraTriggered(const FInputActionValue& Value)
{
	if (const auto PlayerCamera = Cast<APhoenixPlayerCameraManager>(PlayerCameraManager.Get()))
	{
		PlayerCamera->AddTurnInput(Value.Get<float>());
	}
}

void APhoenixPlayerController::OnZoomCameraTriggered(const FInputActionValue& Value)
{
	if (const auto PlayerCamera = Cast<APhoenixPlayerCameraManager>(PlayerCameraManager.Get()))
	{
		PlayerCamera->AddZoomInput(Value.Get<float>());
	}
}

void APhoenixPlayerController::OnSneakStarted()
{
	if (const auto PhoenixCharacter = Cast<APhoenixCharacter>(GetCharacter()))
	{
		PhoenixCharacter->OnSneakActivated();
	}
}

void APhoenixPlayerController::OnGroupSneakStarted()
{
	for (APhoenixCharacter* InCharacter : PartyManagement->GetPartyMembers())
	{
		if (const auto PhoenixCharacter = Cast<APhoenixCharacter>(InCharacter))
		{
			PhoenixCharacter->OnSneakActivated();
		}
	}
}

void APhoenixPlayerController::OnToggleGroupMoveStarted()
{
	bInGroupFollowMode = !bInGroupFollowMode;
}

void APhoenixPlayerController::OnShowInteractablesStarted()
{

}

void APhoenixPlayerController::OnShowInteractablesReleased()
{

}

void APhoenixPlayerController::OnMoveCharacterTriggered(const FInputActionValue& Value)
{
	if (APawn* ControlledPawn = GetPawn())
	{
		// input is a Vector2D
		const FVector2D MovementVector = Value.Get<FVector2D>();

		// find out which way is forward
		const FRotator Rotation = PlayerCameraManager->GetCameraRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement
		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}