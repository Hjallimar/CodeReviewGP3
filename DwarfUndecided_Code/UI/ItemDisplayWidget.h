// (C) 2021 Changemaker Educations (FG20FT GP3 Team 8) - All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemDisplayWidget.generated.h"

USTRUCT(BlueprintType)
struct FDisplayLabelData
{
	GENERATED_BODY()

	FText MainLabel;
};

/**
 * 
 */
UCLASS()
class COOLGP3PROJECT_API UItemDisplayWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemTextBlock;
	
	/* Whether or not the widget is active. */
	bool bIsWidgetActive;

	/* The text data that will be displayed */
	FDisplayLabelData DisplayItemData;

	virtual void DisplayWidget_Impl(const FDisplayLabelData ItemData);
	virtual void HideWidget_Impl();

public:
	/* Makes the widget that displays item information appear. */
	UFUNCTION(BlueprintCallable)
		void DisplayWidget(const FDisplayLabelData ItemData) { DisplayWidget_Impl(ItemData); }

	/* Hides the item information-displaying widget. */
	UFUNCTION(BlueprintCallable)
		void HideWidget() { HideWidget_Impl(); }
};
