// (C) 2021 Changemaker Educations (FG20FT GP3 Team 8) - All Rights Reserved.

// AUTHOR: Justus Hörberg

#include "Other/Triggers/SelfTrigger.h"
#include "Components/ShapeComponent.h"

ASelfTrigger::ASelfTrigger()
{
	//PrimaryActorTick.bCanEverTick = true;

}

void ASelfTrigger::BeginPlay()
{
	Super::BeginPlay();

	if (CollisionComponent)
	{
		CollisionComponent->SetCollisionProfileName("Trigger");
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASelfTrigger::OnTriggerEnter);
		CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ASelfTrigger::OnTriggerExit);
	}
}

void ASelfTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASelfTrigger::BeginDestroy()
{
	Super::BeginDestroy();

	if (CollisionComponent)
	{
		CollisionComponent->OnComponentBeginOverlap.RemoveDynamic(this, &ASelfTrigger::OnTriggerEnter);
		CollisionComponent->OnComponentEndOverlap.RemoveDynamic(this, &ASelfTrigger::OnTriggerExit);
	}
}

void ASelfTrigger::OnTriggerEnter_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ASelfTrigger::OnTriggerExit_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

