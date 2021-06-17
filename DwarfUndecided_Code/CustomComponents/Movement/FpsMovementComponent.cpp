//Author Olof Wallentin - Hazelight
//This class was taken from one of his courses and additions to the original code will be documented
//Class, function and variables may have their names changed without documentation

#include "FpsMovementComponent.h"
#include "FpsMovementStatics.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

void UFpsMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FacingRotationCurrent = FQuat::Slerp(FacingRotationCurrent.Quaternion(), FacingRotationTarget.Quaternion(), FacingRotationSpeed * DeltaTime).Rotator();

	if (FacingRotationCurrent.Equals(FacingRotationTarget))
	{
		FacingRotationCurrent = FacingRotationTarget;
		SetComponentTickEnabled(false);
	}

	FacingRotationSpeed = 1.0f;
}

FFpsMovementStatics UFpsMovementComponent::CreateFrameMovement() const
{
	return FFpsMovementStatics(UpdatedComponent);
}

void UFpsMovementComponent::Move(FFpsMovementStatics& FrameMovement)
{
	FHitResult Hit;
	if (FrameMovement.ShouldApplyGravity())
	{
		SafeMoveUpdatedComponent(FrameMovement.GetGravity(), UpdatedComponent->GetComponentQuat(), true, Hit);
		Hit.Reset();
	}

	FVector Delta = GetMovementDelta(FrameMovement);

	if (!Delta.IsNearlyZero())
	{
		SafeMoveUpdatedComponent(Delta, UpdatedComponent->GetComponentQuat(), true, Hit);

		if (Hit.bBlockingHit)
		{
			Delta = GetMovementDelta(FrameMovement);
		}

		SlideAlongSurface(Delta, 1.0f - Hit.Time, Hit.Normal, Hit);
	}

	FrameMovement.Hit = Hit;
	FrameMovement.FinalLocation = UpdatedComponent->GetComponentLocation();
}

void UFpsMovementComponent::SetFacingRotation(const FRotator& InFacingRotation, float InRotationSpeed)
{
	Internal_SetFacingRotation(InFacingRotation, InRotationSpeed);
}

void UFpsMovementComponent::SetFacingRotation(const FQuat& InFacingRotation, float InRotationSpeed)
{
	Internal_SetFacingRotation(InFacingRotation.Rotator(), InRotationSpeed);
}

void UFpsMovementComponent::SetFacingDirection(const FVector& InFacingDirection, float InRotationSpeed)
{
	Internal_SetFacingRotation(InFacingDirection.Rotation(), InRotationSpeed);
}

void UFpsMovementComponent::Internal_SetFacingRotation(const FRotator& InFacingRotation, float InRotationSpeed)
{
	FRotator NewRotation = InFacingRotation;
	NewRotation.Roll = 0.0f;
	NewRotation.Pitch = 0.0f;
	FacingRotationTarget = NewRotation;

	if (InRotationSpeed < 0.0f)
	{
		FacingRotationCurrent = NewRotation;
		SetComponentTickEnabled(false);
	}
	else
	{
		SetComponentTickEnabled(true);
		FacingRotationSpeed = InRotationSpeed;
	}
}

FVector UFpsMovementComponent::GetMovementDelta(const FFpsMovementStatics& FrameMovement) const
{
	return FrameMovement.GetMovementDelta();
}