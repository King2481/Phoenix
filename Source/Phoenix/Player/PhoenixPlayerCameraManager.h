// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "PhoenixPlayerCameraManager.generated.h"

struct FRuntimeCurveFloat;

/**
 * 
 */
UCLASS()
class PHOENIX_API APhoenixPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:

	APhoenixPlayerCameraManager();

	void AddMoveInput(const FVector2D& InputValue);

	void AddTurnInput(const float InputValue);

	void AddZoomInput(const float InputValue);

	void UpdateFreeCamStatus(const bool bNewStatus);
	
protected:

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(BlueprintReadOnly, Category = "Player Camera Manager")
	TObjectPtr<AActor> FluidSimActorInstance;

	UPROPERTY(BlueprintReadOnly, Category = "Player Camera Manager")
	float CurrentZoomValue;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Player Camera Manager")
	FVector2D ZoomValueRanges;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Player Camera Manager")
	float CurrentTurnValue;

	UPROPERTY(BlueprintReadOnly, Category = "Player Camera Manager")
	float CameraMoveSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Player Camera Manager")
	float CameraTurnSpeed;

	virtual void UpdateViewTargetInternal(FTViewTarget& OutVT,float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Player Camera Manager")
	FRuntimeFloatCurve CameraZoomToHeightDistanceCurve;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Player Camera Manager")
	FRuntimeFloatCurve CameraZoomToLengthDistanceCurve;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Player Camera Manager")
	FRuntimeFloatCurve CameraZoomToPitchCurve;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Player Camera Manager")
	float LocationInterpSpeed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Player Camera Manager")
	float RotationInterpSpeed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Player Camera Manager")
	FBox BoundsBox;

private:

	bool bIsInFreeCam;

	FVector2D MoveInput;

	float CurrentZoomValueAsAlpha;
	FVector LastBaseLocation;

	FTransform TargetTransform;
	FTransform CurrentTransform;
};
