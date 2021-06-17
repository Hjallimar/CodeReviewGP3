// (C) 2021 Changemaker Educations (FG20FT GP3 Team 8) - All Rights Reserved.


#include "UI/GoldWidgetComponent.h"

#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"
#include "GameSystem/GP_GameInstance.h"

UGoldWidgetComponent::UGoldWidgetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UGoldWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	
	UGP_GameInstance* Inst = GetWorld()->GetGameInstance<UGP_GameInstance>();

	// Try adding gold delegate.
	if (Inst)
	{
		//Inst->OnGoldChangedDelegate.AddDynamic(this, &UGoldWidgetComponent::OnGoldChanged);
	}
	
}

void UGoldWidgetComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);
	
	UGP_GameInstance* Inst = GetWorld()->GetGameInstance<UGP_GameInstance>();

	// Try deleting gold delegate.
	if (Inst)
	{
		//Inst->OnGoldChangedDelegate.RemoveDynamic(this, &UGoldWidgetComponent::OnGoldChanged);
	}
}

void UGoldWidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsCurrentlyApproachingGoldValue)
	{
		RepresentedGoldValue = InterpByType(RepresentedGoldValue, PreviousGoldValue, TargetGoldValue, InterpolationDuration, DeltaTime, GoldInterpolationType);
	}
}

void UGoldWidgetComponent::OnGoldChanged(int OldGoldValue, int NewGoldValue)
{
	TargetGoldValue = NewGoldValue;

	if (!bIsCurrentlyApproachingGoldValue)
	{
		PreviousGoldValue = OldGoldValue;
		bIsCurrentlyApproachingGoldValue = true;
	}
}

FString UGoldWidgetComponent::GetNumberInGoldFormat(int Value)
{
	const FString CharFormat(TEXT("00000000"));
	const FString ChZero = TEXT("0");
	
	// Loop back around if exceeding the max allowed by the format.
	Value = Value % (int)FMath::Pow(10, CharFormat.Len());

	FString NumToStr = FString::FromInt(Value);

	FString FullStr;
	// Build the string. Fill irrelevant digits with zeroes first.
	for (int Index = 0; Index < CharFormat.Len(); Index++)
	{
		// If NumIndex returns a negative number, keep adding zeroes.
		const int NumIndex = NumToStr.Len() - (CharFormat.Len() + Index);

		// Once NumIndex reaches an indexable number, just fill the rest of the string with NumToStr.
		if (NumIndex < 0)
			FullStr += ChZero;
		else if (NumIndex < NumToStr.Len())
		{
			FullStr += NumToStr;
			break;
		}
			
	}

	return FullStr;
}

void UGoldWidgetComponent::OnNewGoldValueSet(float Value)
{
	UUserWidget* DisplayWidget = GetWidget();
	if (DisplayWidget)
	{
		UWidgetTree* Tree = DisplayWidget->WidgetTree;
		if (Tree)
		{
			FName NameOfTextWidget = TEXT("GoldValue");

			// Convert the value to gold display format and make that the widget text.
			UTextBlock* TextBlock = Cast<UTextBlock>(Tree->FindWidget(NameOfTextWidget));
			if (TextBlock)
			{
				FString NewTextValue = GetNumberInGoldFormat(FMath::FloorToInt(Value));
				TextBlock->Text.FromString(NewTextValue);
			}
		}
	}
}

float UGoldWidgetComponent::InterpByType(int CurrentValue, int PreviousValue, int TargetValue, float Duration, float DeltaTime, EGoldSetTypee InterpType)
{
	if (InterpType == EGoldSetTypee::Instant)
		return TargetValue;

	float Delta = FMath::Abs(TargetValue - PreviousValue);
	
	float OutValue;
	float IntrpSpeed;
	switch (InterpType)
	{
	default:
	case EGoldSetTypee::FastConstant:
		IntrpSpeed = (float)Delta / Duration;
		OutValue = FMath::FInterpConstantTo(CurrentValue, TargetValue, DeltaTime, IntrpSpeed);
		break;

	case EGoldSetTypee::FastToSlow:
		IntrpSpeed = FMath::Clamp<float>(FMath::Abs((float)CurrentValue / TargetValue) + ((float)DeltaTime / Duration), 0, 1.f);
		OutValue = FMath::InterpExpoIn<float>(CurrentValue, TargetValue, IntrpSpeed);
		break;
	}

	return OutValue;
}