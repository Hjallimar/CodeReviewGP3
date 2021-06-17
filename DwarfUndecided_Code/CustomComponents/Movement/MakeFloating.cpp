//Author Johan Liljedahl
#include "CustomComponents/Movement/MakeFloating.h"

UMakeFloating::UMakeFloating()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UMakeFloating::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
}

void UMakeFloating::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(Active)
	{
		MakeFloat(DeltaTime);
		MakeRotate(DeltaTime);	
	}
}
FVector aaa;
void UMakeFloating::MakeFloat(float DeltaTime)
{
	FVector newLocation = Owner->GetActorLocation();
	float DeltaHeight = FMath::Sin(Value + DeltaTime) - FMath::Sin(Value);
	newLocation.Z += DeltaHeight * Height;
	Value += DeltaTime * Speed;
	Owner->SetActorLocation(newLocation);
}

void UMakeFloating::MakeRotate(float Deltatime)
{
	FRotator newRotation = Owner->GetActorRotation();
	newRotation.Yaw += RotationSpeed * Deltatime;
	Owner->SetActorRotation(newRotation);
}
