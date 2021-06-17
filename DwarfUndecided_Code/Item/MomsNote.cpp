// (C) 2021 Changemaker Educations (FG20FT GP3 Team 8) - All Rights Reserved.
// AUTHOR: Justus Hörberg

#include "Item/MomsNote.h"
#include "CustomComponents/InteractableComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

AMomsNote::AMomsNote()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMomsNote::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMomsNote::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

