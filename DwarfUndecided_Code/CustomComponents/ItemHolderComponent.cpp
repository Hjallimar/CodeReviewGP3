// Author Johan Liljedahl
#include "CustomComponents/ItemHolderComponent.h"


#include "DrawDebugHelpers.h"
#include "Item/BaseItem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Actor.h"
#include "GameSystem/GM_CustomerController.h"
#include "Item/BaseItem_DataAsset.h"
#include "Item/ItemCounter.h"
#include "Kismet/GameplayStatics.h"


UItemHolderComponent::UItemHolderComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	Interactable = CreateDefaultSubobject<UInteractableComponent>(TEXT("Interactable"));
	Interactable->OnPlayerHover.AddDynamic(this, &UItemHolderComponent::OnPlayerHover);
	Interactable->OnPlayerStopHover.AddDynamic(this, &UItemHolderComponent::OnPlayerStopHover);
}

void UItemHolderComponent::BeginPlay()
{
	Super::BeginPlay();
	MyGameMode = Cast<AGP3GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	
	auto temp1 = GetOwner()->GetComponentsByTag(UStaticMeshComponent::StaticClass(), "Allowed");
	OverlayMeshAllowed = Cast<UStaticMeshComponent>(temp1.Last());
	OverlayMeshAllowed->SetCollisionProfileName("NoCollision");
	OverlayMeshAllowed->SetGenerateOverlapEvents(false);
	OverlayMeshAllowed->bHiddenInGame = true;

	auto temp2 = GetOwner()->GetComponentsByTag(UStaticMeshComponent::StaticClass(), "Denied");
	OverlayMeshDenied = Cast<UStaticMeshComponent>(temp2.Last());
	OverlayMeshDenied->SetCollisionProfileName("NoCollision");
	OverlayMeshDenied->SetGenerateOverlapEvents(false);
	OverlayMeshDenied->bHiddenInGame = true;
	
	if(AllowedStockTypes.Contains(EStockType::Currency))
	{
		MyGameMode->GetCustomerController()->AssignCurrencyCounter(this);
	}
	SceneComponentList = GetOwner()->GetComponentsByTag(USceneComponent::StaticClass(), "ItemPosition");
	if(SceneComponentList.Num() > 0)
	{
		ItemPosition = Cast<USceneComponent>(SceneComponentList.Last())->GetComponentLocation();	
	}
	if(CurrentItem == nullptr)
	{
		ScanForItems();
	}
}

void UItemHolderComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UItemHolderComponent::OnPlayerHover(AActor* Player)
{
	if(Cast<UItemCarryPositionComponent>(Player->GetComponentByClass(UItemCarryPositionComponent::StaticClass()))->CurrentItem != nullptr)
	{
		auto Item = Cast<UItemCarryPositionComponent>(Player->GetComponentByClass(UItemCarryPositionComponent::StaticClass()))->CurrentItem;
		if(AllowedStockTypes.Contains(Item->ItemStats->StockType) && Item->ItemStats->CanHangOnWalls == WallSlot && Item != nullptr)
		{
			OverlayMeshAllowed->SetHiddenInGame(false);
		}
		else
		{
			OverlayMeshDenied->SetHiddenInGame(false);
			
			if(Item->ItemStats->StockType != EStockType::Currency && this->GetOwner()->IsA(AItemCounter::StaticClass())) //UNLESS ITS MONEY
			{
				OverlayMeshDenied->SetHiddenInGame(true);
				OverlayMeshAllowed->SetHiddenInGame(false);
			}
		}
	}
	if(CurrentItem != nullptr)
	{
		CurrentItem->OnPlayerHover(Player);
	}
}

void UItemHolderComponent::OnPlayerStopHover(AActor* Player)
{
	OverlayMeshAllowed->SetHiddenInGame(true);
	OverlayMeshDenied->SetHiddenInGame(true);
	
	if(CurrentItem != nullptr)
	{
		CurrentItem->OnPlayerStopHover(Player);
	}
}

void UItemHolderComponent::MakeItemCurrent(AActor* Item)
{
	if (Item == nullptr){return;}
	
	Item->SetActorLocation(ItemPosition);
	Item->SetActorRotation(GetOwner()->GetActorRotation());
	CurrentItem = Cast<ABaseItem>(Item);
	CurrentItem->CurrentItemHolder = this;
	if(GetOwner()->IsA(AItemCounter::StaticClass()) && CurrentItem->ItemStats->CanHangOnWalls)
	{
		CurrentItem->SetActorRotation(FRotator(-0.000309,-29.999817,-89.999886));
	}
}
void UItemHolderComponent::SwapItem(AActor* Item)
{
	CurrentItem->CurrentItemHolder = nullptr;
	LastItem = CurrentItem;
	CurrentItem = Cast<ABaseItem>(Item);
	CurrentItem->OnPlayerStopInteract();
	CurrentItem->CurrentItemHolder = this;
	CurrentItem->SetActorLocation(ItemPosition);
	CurrentItem->SetActorRotation(GetOwner()->GetActorRotation());
}
void UItemHolderComponent::MakeItemNull()
{
	if(CurrentItem != nullptr)
	{
		CurrentItem = nullptr;	
	}
}

void UItemHolderComponent::ScanForItems()
{
	ETraceTypeQuery TraceType = UEngineTypes::ConvertToTraceType(ECC_WorldDynamic);
	IgnoreList.Add(GetOwner());
	UKismetSystemLibrary::SphereTraceMulti(GetWorld(), ItemPosition, ItemPosition + GetOwner()->GetActorUpVector() * 10, 20, TraceType, false, IgnoreList, EDrawDebugTrace::None, Hits, true, FColor::White, FColor::Green, 10);
	//DrawDebugSphere(GetWorld(), ItemPosition + GetOwner()->GetActorUpVector() * 10, 20, 10, FColor::White, true);
	for (FHitResult Hit : Hits)
	{
		if(Hit.bBlockingHit && Hit.GetActor() != nullptr)
		{
			if (Hit.GetActor()->IsA<ABaseItem>())
			{
				auto Item = Cast<ABaseItem>(Hit.GetActor());
				EStockType StockType = Item->ItemStats->StockType;
				if(AllowedStockTypes.Contains(StockType) && Item->ItemStats->CanHangOnWalls == WallSlot)
				{
					MakeItemCurrent(Hit.GetActor());
					UE_LOG(LogTemp, Log, TEXT("ItemSlot Found Item, Making %s CurrentItem"), *CurrentItem->GetName());
				}
				else
				{
					//UKismetSystemLibrary::DrawDebugSphere(GetWorld(),ItemPosition,15, 4, FColor::Red, 60, 1);
				}
			}
				//return;
		}	
	}
}

