//Author: Hjalmar Andersson

#pragma once
#include "Components/ActorComponent.h"
#include "CustomerComponent.generated.h"

class UBaseItem_DataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCustomerEvent, UBaseItem_DataAsset*, ItemStats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRequestEvent);
UCLASS(Meta = (BlueprintSpawnableComponent))
class UCustomerComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UCustomerComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	UBaseItem_DataAsset* TargetItem;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FRequestEvent RequestItem;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FCustomerEvent CompareItem;

	UFUNCTION()
	void MakePuchase();
};