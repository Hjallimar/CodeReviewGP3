//Author Olof Wallentin - Hazelight
//This class was taken from one of his courses and additions to the original code will be documented
//Class, function and variables may have their names changed without documentation

#include "FpsMovementStatics.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"

FFpsMovementStatics::FFpsMovementStatics(AActor* InActor)
{
	StartLocation = InActor->GetActorLocation();
}

FFpsMovementStatics::FFpsMovementStatics(USceneComponent* InSceneComponent)
{
	StartLocation = InSceneComponent->GetComponentLocation();
}

void FFpsMovementStatics::AddDelta(const FVector& InDelta)
{
	MovementDelta += InDelta;
}
