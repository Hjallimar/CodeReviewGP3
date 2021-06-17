// (C) 2021 Changemaker Educations (FG20FT GP3 Team 8) - All Rights Reserved.

// AUTHOR: Justus Hörberg

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "ItemDisplayWidgetComponent.generated.h"

USTRUCT(BlueprintType)
struct FDisplayLabelDataa
{
	GENERATED_BODY()
	
	FString MainLabel;
};

/**
 * 
 */
UCLASS()
class COOLGP3PROJECT_API UItemDisplayWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UItemDisplayWidgetComponent();

	virtual void BeginPlay() override;

protected:
	/* Whether or not the widget is active. */
	bool bIsWidgetActive;

	/* The text data that will be displayed */
	FDisplayLabelDataa DisplayItemData;

	/* The name of the Text Block widget in the UserWidget that will display the item text. */
	UPROPERTY(EditDefaultsOnly)
	FName NameOfTextWidget;// = TEXT("MainLabel");

	virtual void DisplayWidget_Impl(const FDisplayLabelDataa ItemData);
	virtual void HideWidget_Impl();
	
public:
	/* Makes the widget that displays item information appear. */
	UFUNCTION(BlueprintCallable)
	void DisplayWidget(const FDisplayLabelDataa ItemData) { DisplayWidget_Impl(ItemData); }
	
	/* Hides the item information-displaying widget. */
	UFUNCTION(BlueprintCallable)
	void HideWidget() { HideWidget_Impl(); }
};
