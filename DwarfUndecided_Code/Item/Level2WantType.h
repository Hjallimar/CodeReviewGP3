#pragma once

#include "CoreMinimal.h"
#include "Level2WantType.generated.h"

UENUM()
/* The type of item (DamageType/WeaponType) customers want, since they can ask for either one or the other. */
enum class ELevel2WantType
{
	DamageType = 0,
	WeaponType
};