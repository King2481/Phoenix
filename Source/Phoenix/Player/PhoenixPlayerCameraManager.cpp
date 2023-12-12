// Created by Bruce Crum.


#include "Phoenix/Player/PhoenixPlayerCameraManager.h"

APhoenixPlayerCameraManager::APhoenixPlayerCameraManager()
{
	CurrentZoomValue = 0.0f;
	ZoomValueRanges = FVector2D::ZeroVector;
	CurrentTurnValue = 0.0f;

	bIsInFreeCam = false;
	CurrentZoomValueAsAlpha = 0.0f;
	CameraMoveSpeed = 1000.0f;
	CameraTurnSpeed = 500.0f;

	TargetTransform = FTransform::Identity;
	CurrentTransform = FTransform::Identity;
	LastBaseLocation = FVector::ZeroVector;
	LocationInterpSpeed = 5.0f;
	RotationInterpSpeed = 2.5f;
	BoundsBox = FBox();
}

void APhoenixPlayerCameraManager::UpdateViewTargetInternal(FTViewTarget& OutVT, float DeltaTime)
{
	if (OutVT.Target)
	{
		// Bounds
		{
			BoundsBox = BoundsBox.MoveTo(OutVT.Target->GetActorLocation());
		}

		// Vectors
		{
			FVector FinalLocation = FVector::ZeroVector;
			const FVector BaseLocation = bIsInFreeCam ? LastBaseLocation : OutVT.Target->GetActorLocation();

			if (bIsInFreeCam)
			{
				// Get the camera's right and forward vectors in world space
				const FVector CameraRight = FVector::CrossProduct(FVector::UpVector, GetCameraRotation().Vector()).GetSafeNormal();
				const FVector CameraForward = GetCameraRotation().Vector().GetSafeNormal();

				FVector MovementDirection = (CameraRight * MoveInput.X) + (CameraForward * MoveInput.Y);
				MovementDirection.Z = 0.0f;

				FinalLocation += BaseLocation + MovementDirection * CameraMoveSpeed * DeltaTime;
			}
			else
			{
				FinalLocation = BaseLocation;
			}

			LastBaseLocation = FinalLocation;

			// The final locations Z coordinate's should be relative to the ViewTarget.
			FinalLocation.Z = OutVT.Target->GetActorLocation().Z + CameraZoomToHeightDistanceCurve.GetRichCurveConst()->Eval(CurrentZoomValueAsAlpha);

			// Calculate the angle based on the turn value
			float const RotationAngle = FMath::DegreesToRadians(CurrentTurnValue);
			const float CurrentFollowDistance = CameraZoomToLengthDistanceCurve.GetRichCurveConst()->Eval(CurrentZoomValueAsAlpha);
			FinalLocation += FVector(FMath::Cos(RotationAngle), FMath::Sin(RotationAngle), 0.0f) * CurrentFollowDistance;

			// Clamp the location within bounds.
			FinalLocation.X = FMath::Clamp(FinalLocation.X, BoundsBox.Min.X, BoundsBox.Max.X);
			FinalLocation.Y = FMath::Clamp(FinalLocation.Y, BoundsBox.Min.Y, BoundsBox.Max.Y);
			FinalLocation.Z = FMath::Clamp(FinalLocation.Z, BoundsBox.Min.Z, BoundsBox.Max.Z);

			TargetTransform.SetLocation(FinalLocation);
		}

		// Quats
		{
			FRotator Rotation = FRotator::ZeroRotator;
			Rotation.Pitch = CameraZoomToPitchCurve.GetRichCurveConst()->Eval(CurrentZoomValueAsAlpha);
			Rotation.Yaw = CurrentTurnValue;

			TargetTransform.SetRotation(FQuat::MakeFromRotator(Rotation));
		}

		// Update the transforms
		CurrentTransform.SetLocation(FMath::VInterpTo(CurrentTransform.GetLocation(), TargetTransform.GetLocation(), DeltaTime, LocationInterpSpeed));
		CurrentTransform.SetRotation(FMath::QInterpTo(CurrentTransform.GetRotation(), TargetTransform.GetRotation(), DeltaTime, RotationInterpSpeed));

		// Final POV
		OutVT.POV.Location = CurrentTransform.GetLocation();
		OutVT.POV.Rotation = CurrentTransform.GetRotation().Rotator();
		OutVT.POV.DesiredFOV = 90.0f;
	}
	else
	{
		Super::UpdateViewTargetInternal(OutVT, DeltaTime);
	}
}

void APhoenixPlayerCameraManager::AddMoveInput(const FVector2D& InputValue)
{
	UpdateFreeCamStatus(true);
	MoveInput = InputValue;
}

void APhoenixPlayerCameraManager::AddTurnInput(const float InputValue)
{
	CurrentTurnValue = FMath::Wrap<float>((CurrentTurnValue - InputValue), 0.0f, 360.f);
}

void APhoenixPlayerCameraManager::AddZoomInput(const float InputValue)
{
	CurrentZoomValue = FMath::Clamp<float>(CurrentZoomValue + InputValue, ZoomValueRanges.X, ZoomValueRanges.Y);
	CurrentZoomValueAsAlpha = (CurrentZoomValue - ZoomValueRanges.X) / (ZoomValueRanges.Y - ZoomValueRanges.X);
}

void APhoenixPlayerCameraManager::UpdateFreeCamStatus(const bool bNewStatus)
{
	bIsInFreeCam = bNewStatus;
}