// (C) 2021 Changemaker Educations (FG20FT GP3 Team 8) - All Rights Reserved.

// AUTHOR: Justus Hörberg


#include "Other/Triggers/BoxSelfTrigger.h"
#include "Components/BoxComponent.h"

ABoxSelfTrigger::ABoxSelfTrigger()
{
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>("Collision Component");
}