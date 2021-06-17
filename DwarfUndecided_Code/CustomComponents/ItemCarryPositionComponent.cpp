//Author Johan Liljedahl
//Secondary author: Hjalmar Andersson

#include "CustomComponents/ItemCarryPositionComponent.h"

#include "DrawDebugHelpers.h"
#include "ItemHolderComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameSystem/GM_BargainComponent.h"
#include "Item/BaseItem.h"
#include "Item/BaseItem_DataAsset.h"
#include "Item/GoldChest.h"
#include "Item/ItemCounter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/PlayerCharacter.h"


UItemCarryPositionComponent::UItemCarryPositionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UItemCarryPositionComponent::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<APlayerCharacter>(GetOwner());
	MyGameMode = Cast<AGP3GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	CarryPositionList = GetOwner()->GetComponentsByTag(USceneComponent::StaticClass(), "CarryPosition"); //Find The Scene Component
	CarryPosition = Cast<USceneComponent>(CarryPositionList.Last());
	CachedScale = FVector(1,1,1);
}

void UItemCarryPositionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(InteractingWithItem && CurrentItem != nullptr) // Carry the current Item
	{
		CarryItem();
	}
}
void UItemCarryPositionComponent::CarryItem()
{
	CurrentItem->SetActorLocation(CarryPosition->GetComponentLocation());
	CurrentItem->SetActorRotation(CarryPosition->GetComponentRotation());
	CurrentItem->SetActorScale3D(FVector(0.15,0.15,0.15));
}

// Hit Item! //
void UItemCarryPositionComponent::InteractWithItem(AActor* InteractItem)
{
	ABaseItem* HitItem = Cast<ABaseItem>(InteractItem);
	if(CurrentItem == nullptr || CurrentItem == HitItem)
	{
		Item_PickUpItem(HitItem);
	}
	else if(CurrentItem != HitItem && CurrentItem->GetActorLocation() == CarryPosition->GetComponentLocation())
	{
		Item_SwapItem(HitItem);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("SHOULD NOT HAPPEN"));
	}
}
void UItemCarryPositionComponent::Item_PickUpItem(ABaseItem* HitItem)
{
	CurrentItem = Cast<ABaseItem>(HitItem);
	if(CurrentItem->CurrentItemHolder != nullptr)
	{
		CurrentItem->CurrentItemHolder->MakeItemNull();
		CurrentItem->CurrentItemHolder->RemoveItem.Broadcast(nullptr);
	}
	CurrentItem->OnPlayerInteract();
	InteractingWithItem = true;
	UE_LOG(LogTemp, Log, TEXT("Hand Empty - Picking Up Item"));
}
void UItemCarryPositionComponent::Item_SwapItem(ABaseItem* HitItem)
{
	if (HitItem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("HitItem is nullptr!"));
	}
	else if (HitItem->CurrentItemHolder == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemHolder is nullptr!"));
		return;
	}
	else if (HitItem->CurrentItemHolder->GetOwner() == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner is nullptr!"));
	}
	AActor* Target = HitItem->CurrentItemHolder->GetOwner();
	InteractWithCounter(Target);
}

// Hit ItemSlot! //
void UItemCarryPositionComponent::InteractWithCounter(AActor* InteractItem)
{
	ItemHolder = InteractItem->FindComponentByClass<UItemHolderComponent>();
	if(CurrentItem != nullptr)
	{
		CheckIfEligible(CurrentItem);
		CurrentItem->OnPlayerHover(GetOwner()); //enable highlighting for item before swapping
	}
	if (ItemHolder == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("You have no CounterTop"));
		return;
	}
	if(ItemHolder->CurrentItem != nullptr && CurrentItem != nullptr && CurrentItemIsEligible)
	{
		//CurrentItem->OnPlayerHover(GetOwner()); //enable highlighting for item before swapping
		Counter_SwapItem();
		//CurrentItem->OnPlayerStopHover(GetOwner()); // remove highlighting for held item
	}
	else if(ItemHolder->CurrentItem == nullptr && CurrentItem != nullptr && CurrentItemIsEligible)
	{
		//CurrentItem->OnPlayerHover(GetOwner()); //enable highlighting for item before swapping
		Counter_PlaceItem();
	}
	else if (CurrentItem == nullptr && ItemHolder->CurrentItem != nullptr)
	{
		Counter_PickUpItem();
		//CurrentItem->OnPlayerStopHover(GetOwner()); // remove highlighting for held item
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("ITEM CANNOT "));
	}
	if(CurrentItem != nullptr)
	{
		CurrentItem->OnPlayerStopHover(GetOwner()); // remove highlighting for held item	
	}
}
void UItemCarryPositionComponent::Counter_SwapItem()
{
	CurrentItemIsEligible = false;
	CurrentItem->SetActorScale3D(CachedScale);
	ItemHolder->SwapItem(CurrentItem);
	ItemHolder->ReceiveItem.Broadcast(CurrentItem);
	CurrentItem->OnPlayerStopInteract();
	CurrentItem = Cast<ABaseItem>(ItemHolder->LastItem);
	CurrentItem->OnPlayerInteract();
	UE_LOG(LogTemp, Log, TEXT("Holding Item - Clicked ItemSlot - Swap Items"));
}
void UItemCarryPositionComponent::Counter_PlaceItem()
{
	CurrentItemIsEligible = false;
	CurrentItem->SetActorScale3D(CachedScale);
	InteractingWithItem = false;
	ItemHolder->MakeItemNull();
	ItemHolder->MakeItemCurrent(CurrentItem);
	ItemHolder->ReceiveItem.Broadcast(CurrentItem);
	CurrentItem->OnPlayerStopInteract();
	CurrentItem = nullptr;
	UE_LOG(LogTemp, Log, TEXT("Clicked Empty Countertop - Placing Item"));
}
void UItemCarryPositionComponent::Counter_PickUpItem()
{
	CurrentItem = ItemHolder->CurrentItem;
	CurrentItem->OnPlayerInteract();
	InteractingWithItem = true;
	ItemHolder->MakeItemNull();
	CurrentItem->CurrentItemHolder->RemoveItem.Broadcast(nullptr);
	UE_LOG(LogTemp, Log, TEXT("Hand Empty - Clicked NON Empty Countertop - Picking Up Item"));
}

// Hit GoldChest! //
void UItemCarryPositionComponent::InteractWithGoldChest(AActor* HitChest)
{
	if(CurrentItem != nullptr && CurrentItem->ItemStats->StockType == EStockType::Currency)
	{
		auto Chest = Cast<AGoldChest>(HitChest);
		Chest->AddGold(CurrentItem->ItemStats->Value);
		Chest->OnPlayerStopHover(GetOwner());
		Chest->OnPlayerHover(GetOwner());
		CurrentItem->DeleteThisItem();
		CurrentItem = nullptr;
		UE_LOG(LogTemp, Log, TEXT("Gold placed"));
	}
	else{return;}
}

// Check ItemSlot Restrictions //
void UItemCarryPositionComponent::CheckIfEligible(ABaseItem* Item)
{
	if(Item != nullptr)
	{
		ETraceTypeQuery TraceType = UEngineTypes::ConvertToTraceType(ECC_WorldDynamic);
		IgnoreList.Add(Item);
		IgnoreList.Add(GetOwner());
		auto Origin = Cast<APlayerCharacter>(GetOwner())->Origin;
		auto End = Cast<APlayerCharacter>(GetOwner())->End;
		UKismetSystemLibrary::LineTraceSingle(this, Origin, End, TraceType, false, IgnoreList, EDrawDebugTrace::None, Hit, true);
		if(Hit.GetActor()->IsA(AItemCounter::StaticClass()) && Item->ItemStats->StockType != EStockType::Currency)
		{
			CurrentItemIsEligible = true;
			IgnoreList.Empty();
			return;
		}
		IgnoreList.Empty();
		if (Hit.GetActor()->GetComponentByClass(UItemHolderComponent::StaticClass())) //Checking the counter restrictions
		{
			CheckIfCounterAllows(Item);
		}
		else //If Swapping Items - Checking the counter restrictions
		{
			CheckIfItemCanBeSwapped(Item);
		}
	}
}
void UItemCarryPositionComponent::CheckIfCounterAllows(ABaseItem* Item)
{
	UItemHolderComponent* ItemSlot = Hit.GetActor()->FindComponentByClass<UItemHolderComponent>();
	if (ItemSlot != nullptr)
	{
		EStockType StockType = Item->ItemStats->StockType;
		if(ItemSlot->AllowedStockTypes.Contains(StockType) && ItemSlot->WallSlot == Item->ItemStats->CanHangOnWalls)
		{
			CurrentItemIsEligible = true;
			//UE_LOG(LogTemp, Log, TEXT("ITEM IS ELIGIBLE FOR THIS SLOT"));
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("ALLOWED-STOCK-TYPES DOES NOT CONTAIN THIS TYPE"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("ITEM IS NOT ELIGIBLE FOR THIS SLOT"));
	}
}
void UItemCarryPositionComponent::CheckIfItemCanBeSwapped(ABaseItem* Item)
{
	UItemHolderComponent* ItemSlot = Cast<ABaseItem>(Hit.GetActor())->CurrentItemHolder;
	if (ItemSlot != nullptr)
	{
		EStockType StockType = Item->ItemStats->StockType;
		if((ItemSlot->AllowedStockTypes.Contains(StockType) && ItemSlot->WallSlot == Item->ItemStats->CanHangOnWalls) || (ItemSlot->GetOwner()->IsA(AItemCounter::StaticClass()) && StockType != EStockType::Currency))
		{
			CurrentItemIsEligible = true;
			//UE_LOG(LogTemp, Log, TEXT("TRYING TO SWAP - ITEM IS ELIGIBLE FOR THIS SLOT"));
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("TRYING TO SWAP - ALLOWED-STOCK-TYPES DOES NOT CONTAIN THIS TYPE"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("TRYING TO SWAP - ITEM IS NOT ELIGIBLE FOR THIS SLOT"));
	}	
}

