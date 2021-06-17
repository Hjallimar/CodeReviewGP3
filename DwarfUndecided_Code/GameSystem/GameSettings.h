// (C) 2021 Changemaker Educations (FG20FT GP3 Team 8) - All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameSettings.generated.h"

/**
 * Struct containing the game options, such as mouse sensitivity, etc.
 */
USTRUCT()
struct COOLGP3PROJECT_API FGameSettings
{
	GENERATED_BODY()
	
public:
	/* The mouse sensitivity setting. */
	UPROPERTY(EditAnywhere, meta=(ClampMin="0.25", ClampMax="3.0"))
	float MouseSensitivity = 1;


};
