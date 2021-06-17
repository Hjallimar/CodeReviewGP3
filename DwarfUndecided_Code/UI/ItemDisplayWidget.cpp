// (C) 2021 Changemaker Educations (FG20FT GP3 Team 8) - All Rights Reserved.


#include "UI/ItemDisplayWidget.h"

#include "Components/TextBlock.h"

//UItemDisplayWidget::UItemDisplayWidgetComponent()
//{
//	PrimaryComponentTick.bCanEverTick = true;
//	PrimaryComponentTick.bStartWithTickEnabled = true;
//}

void UItemDisplayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ItemTextBlock->SetText(FText::GetEmpty());
}

void UItemDisplayWidget::DisplayWidget_Impl(const FDisplayLabelData ItemData)
{
	if (!bIsWidgetActive)
	{
		if (ItemTextBlock)
		{
			DisplayItemData = ItemData;
			ItemTextBlock->SetText(DisplayItemData.MainLabel);
			
			//if (!IsInViewport())
			//	AddToViewport();

			// Not entirely sure what UWidget::Visibility is supposed to do, but
			// this does the job of hiding the widget fine I guess...
			SetColorAndOpacity(FLinearColor(ColorAndOpacity.R, ColorAndOpacity.G, ColorAndOpacity.B, 1.f));
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("No TextBlock widget named 'MainLabel' could be found in the UserWidget tree!"));
		}

		bIsWidgetActive = true;
	}
}

void UItemDisplayWidget::HideWidget_Impl()
{
	if (bIsWidgetActive)
	{
		// heck does this even do
		//ItemTextBlock->Visibility = ESlateVisibility::Hidden;

		// this just remove the thingy from the vp altogether woot
		//RemoveFromViewport();
		SetColorAndOpacity(FLinearColor(ColorAndOpacity.R, ColorAndOpacity.G, ColorAndOpacity.B, 0.f));
		
		bIsWidgetActive = false;
	}
}
