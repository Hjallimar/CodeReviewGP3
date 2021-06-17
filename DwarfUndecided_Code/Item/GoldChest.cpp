//Author Johan Liljedahl

#include "Item/GoldChest.h"
#include "Kismet/GameplayStatics.h"
#include "UI/ItemDisplayWidget.h"
#include "UI/HUD/GameHUD.h"
#include "CustomComponents/InteractableComponent.h"
#include "GameSystem/GM_BargainComponent.h"
#include "GameSystem/GP3GameMode.h"

AGoldChest::AGoldChest()
{
	PrimaryActorTick.bCanEverTick = true;
	Interactable = CreateDefaultSubobject<UInteractableComponent>(TEXT("Interactable"));
	Transform = CreateDefaultSubobject<USceneComponent>(TEXT("Transform"));
	RootComponent = Transform;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Transform);
	Interactable->OnPlayerHover.AddDynamic(this, &AGoldChest::OnPlayerHover);
	Interactable->OnPlayerStopHover.AddDynamic(this, &AGoldChest::OnPlayerStopHover);
}

void AGoldChest::BeginPlay()
{
	Super::BeginPlay();
	MyGameMode = Cast<AGP3GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	MyGameHUD = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD());
	auto* GM = Cast<AGP3GameMode>(UGameplayStatics::GetGameMode(this));
	GM->GetBargainComponent()->GoldChest = this;
	UpdateGoldInStorage();
	CheckIfMeshShouldChange();
}

void AGoldChest::OnPlayerHover(AActor* Player)
{
	UItemDisplayWidget* ItemDisplayWidget = MyGameHUD->GetItemDisplayWidget();
	ItemDisplayWidget->DisplayWidget(GenerateDisplayItemInfo());
}
void AGoldChest::OnPlayerStopHover(AActor* Player)
{
	if (!Player) return;

	UItemDisplayWidget* ItemDisplayWidget = MyGameHUD->GetItemDisplayWidget();
	if (ItemDisplayWidget)
	{
		ItemDisplayWidget->HideWidget();
	}
}

void AGoldChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGoldChest::AddGold(int Value)
{
	MyGameMode->AddGold(Value);
	GoldInStorage = MyGameMode->GetGold();
	OnGoldAdded();
	CheckIfMeshShouldChange();
}
void AGoldChest::RemoveGold(int Value)
{
	MyGameMode->SetGold(MyGameMode->GetGold()-Value);
	GoldInStorage = MyGameMode->GetGold();
	OnGoldRemoved();
	CheckIfMeshShouldChange();
}

FDisplayLabelData AGoldChest::GenerateDisplayItemInfo()
{
	FDisplayLabelData OutData;
	const FText NullData(FText::FromString(TEXT("ERROR: NO ITEM STATS")));
	FString MainLabel = FString::FromInt(GoldInStorage);
	OutData.MainLabel = FText::FromString(MainLabel + " Gold Coins");

	return OutData;
}

int AGoldChest::GetCurrentGold()
{
	return GoldInStorage;
}

void AGoldChest::UpdateGoldInStorage()
{
	GoldInStorage = MyGameMode->GetGold();
}

void AGoldChest::CheckIfMeshShouldChange()
{
	if(GoldInStorage <= ValueForEmpty)
	{
		Mesh->SetStaticMesh(Meshes[0]); // Empty
	}
	else if(GoldInStorage > ValueForEmpty && GoldInStorage < ValueForPoor)
	{
		Mesh->SetStaticMesh(Meshes[1]); // Poor
	}
	else if(GoldInStorage >= ValueForPoor && GoldInStorage < ValueForNormal )
	{
		Mesh->SetStaticMesh(Meshes[2]); // Normal
	}
	else if(GoldInStorage >= ValueForNormal)
	{
		Mesh->SetStaticMesh(Meshes[3]); // Rich
	}
}

