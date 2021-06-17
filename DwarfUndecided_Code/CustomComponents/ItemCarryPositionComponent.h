//Author Johan
//Secondary Ahutor: Hjalmar Andersson
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameSystem/GP3GameMode.h"

#include "ItemCarryPositionComponent.generated.h"

class UCameraComponent;
class APlayerCharacter;
class USceneComponent;
class UItemHolderComponent;
class ABaseItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COOLGP3PROJECT_API UItemCarryPositionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UItemCarryPositionComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void CarryItem();
	void InteractWithItem(AActor*);
	void Item_PickUpItem(ABaseItem*);
	void Item_SwapItem(ABaseItem*);
	
	void InteractWithCounter(AActor*);
	void Counter_SwapItem();
	void Counter_PlaceItem();
	void Counter_PickUpItem();
	
	void InteractWithGoldChest(AActor*);
	
	void CheckIfEligible(ABaseItem*);
	void CheckIfCounterAllows(ABaseItem*);
	void CheckIfItemCanBeSwapped(ABaseItem*);
	USceneComponent* CarryPosition;
	ABaseItem* CurrentItem;
	bool InteractingWithItem = false;
protected:
	virtual void BeginPlay() override;
	TArray<UActorComponent*> CarryPositionList;
	UItemHolderComponent* ItemHolder;
	AGP3GameMode* MyGameMode;
	FHitResult Hit;
	FHitResult Hit2;
	FVector CachedScale;
	bool CurrentItemIsEligible = false;
	APlayerCharacter* Player;

	TArray<AActor*> IgnoreList; //for ignoring CarriedItem
};
