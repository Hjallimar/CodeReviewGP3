// Author Johan Liljedahl
// Secondary Author: Hjalmar Andersson

#pragma once
#include "InteractableComponent.h"
#include "ItemCarryPositionComponent.h"
#include "Components/ActorComponent.h"
#include "Item/ItemStats.h"
#include "ItemHolderComponent.generated.h"

class AActor;
class ABaseItem;
//HJ
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemHolderEvent, AActor*, Item);
// ClassGroup = (Custom),
UCLASS(Meta=(BlueprintSpawnableComponent) )
class UItemHolderComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UItemHolderComponent();
	//HJ
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FItemHolderEvent ReceiveItem;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FItemHolderEvent RemoveItem;
	//

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void OnPlayerHover(AActor* Player);
	UFUNCTION(BlueprintCallable)
    void OnPlayerStopHover(AActor* Player);
	UPROPERTY(EditAnywhere, Category = ItemPosition)
	bool WallSlot = false;
	UPROPERTY(EditAnywhere, Category = ItemPosition)
	TArray<EStockType> AllowedStockTypes;
	void MakeItemCurrent(AActor* Item);
	void SwapItem(AActor* Item);
	void MakeItemNull();
	void ScanForItems();
	
	ABaseItem* CurrentItem;
	FVector ItemPosition;
	TArray<FHitResult> Hits;
	AActor* LastItem;
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* OverlayMeshAllowed;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* OverlayMeshDenied;
	TArray<AActor*> IgnoreList;
	TArray<UActorComponent*> SceneComponentList;
	AGP3GameMode* MyGameMode;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInteractableComponent* Interactable;
};
