// (C) 2021 Changemaker Educations (FG20FT GP3 Team 8) - All Rights Reserved.


#include "UI/ItemDisplayWidgetComponent.h"

#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"
#include "GameFramework/HUD.h"

UItemDisplayWidgetComponent::UItemDisplayWidgetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UItemDisplayWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UItemDisplayWidgetComponent::DisplayWidget_Impl(const FDisplayLabelDataa ItemData)
{
	if (!bIsWidgetActive)
	{
		UUserWidget* DisplayWidget = GetWidget();
		if (DisplayWidget)
		{
			UWidgetTree* Tree = DisplayWidget->WidgetTree;
			if (Tree)
			{
				UTextBlock* TextBlock = Cast<UTextBlock>(Tree->FindWidget(NameOfTextWidget));
				if (TextBlock)
				{
					DisplayItemData = ItemData;
					TextBlock->Text.FromString(DisplayItemData.MainLabel);

					DisplayWidget->Visibility = ESlateVisibility::Visible;
				}
				else
				{
					UE_LOG(LogTemp, Log, TEXT("No TextBlock widget named 'MainLabel' could be found in the UserWidget tree!"));
				}
			}
		}

		bIsWidgetActive = true;
	}
}

void UItemDisplayWidgetComponent::HideWidget_Impl()
{
	if (bIsWidgetActive)
	{
		UUserWidget* DisplayWidget = GetWidget();
		if (DisplayWidget)
		{
			UWidgetTree* Tree = DisplayWidget->WidgetTree;
			if (Tree)
			{
				UTextBlock* TextBlock = Cast<UTextBlock>(Tree->FindWidget(NameOfTextWidget));
				if (TextBlock)
				{
					DisplayWidget->Visibility = ESlateVisibility::Hidden;
				}
			}
		}

		bIsWidgetActive = false;
	}
}
