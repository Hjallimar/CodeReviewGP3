// Author Johan Liljedahl
// Secondary Author Hjalmar Andersson

#include "ItemCounter.h"
#include "Item/BaseItem.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Item/BaseItem.h"
#include "Item/BaseItem_DataAsset.h"
#include "CustomComponents/ItemHolderComponent.h"
#include "GameSystem/GP3GameMode.h"
#include "GameSystem/GM_BargainComponent.h"
#include "Kismet/GamePlayStatics.h"

AItemCounter::AItemCounter()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetCollisionProfileName("BlockAllDynamic");

	HolderComp = CreateDefaultSubobject<UItemHolderComponent>(TEXT("Item Holder Component"));
	HolderComp->ReceiveItem.AddDynamic(this, &AItemCounter::ReceiveItem);
	HolderComp->RemoveItem.AddDynamic(this, &AItemCounter::RemoveItem);
}

void AItemCounter::BeginPlay()
{
	Super::BeginPlay();
	auto* GM = Cast<AGP3GameMode>(UGameplayStatics::GetGameMode(this));
	if (GM == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No GameMode detected"));
		return;
	}

	BargainComp = GM->FindComponentByClass<UGM_BargainComponent>();
	if(BargainComp == nullptr) 
	{
		UE_LOG(LogTemp, Warning, TEXT("No Bargain component detected"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("We have a gamemode and bargain!!"));
}

void AItemCounter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItemCounter::ReceiveItem(AActor* Item)
{
	if (Item != nullptr)
	{
		if (BargainComp == nullptr)
			return;
		HolderComp->MakeItemCurrent(Item);
		BargainComp->AssignItem(HolderComp->CurrentItem);
	}
	else
		HolderComp->MakeItemNull();
}

void AItemCounter::RemoveItem(AActor* Item)
{
	BargainComp->AssignItem(nullptr);
}

