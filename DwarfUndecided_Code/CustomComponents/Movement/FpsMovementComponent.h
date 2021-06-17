//Author Olof Wallentin - Hazelight
//This class was taken from one of his courses and additions to the original code will be documented
//Class, function and variables may have their names changed without documentation

#pragma once
#include "GameFramework/MovementComponent.h"
#include "FpsMovementComponent.generated.h"

struct FFpsMovementStatics;

UCLASS()
class UFpsMovementComponent : public UMovementComponent
{
	GENERATED_BODY()
public:

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FFpsMovementStatics CreateFrameMovement() const;

	void Move(FFpsMovementStatics& FrameMovement);

	FRotator GetFacingRotation() const { return FacingRotationCurrent; }
	FVector GetFacingDirection() const { return FacingRotationCurrent.Vector(); }

	void SetFacingRotation(const FRotator& InFacingRotation, float InRotationSpeed = -1.0f);
	void SetFacingRotation(const FQuat& InFacingRotation, float InRotationSpeed = -1.0f);
	void SetFacingDirection(const FVector& InFacingDirection, float InRotationSpeed = -1.0f);

private:
	void Internal_SetFacingRotation(const FRotator& InFacingRotation, float InRotationSpeed);
	FVector GetMovementDelta(const FFpsMovementStatics& FrameMovement) const;

	FRotator FacingRotationCurrent;
	FRotator FacingRotationTarget;
	float FacingRotationSpeed;
};