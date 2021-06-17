// Author Johan Liljedahl
// Secondary Author Hjalmar Andersson

#pragma once
#include "GameFramework/Actor.h"
#include "ItemCounter.generated.h"

class USceneComponent;
class UBoxComponent;
class ABaseCustomer;
class ABaseItem;
class UItemHolderComponent;
class UGM_BargainComponent;

UCLASS()
class AItemCounter : public AActor
{
	GENERATED_BODY()
public:
	AItemCounter();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = ItemPosition) 
	FVector ItemPosition;

	UFUNCTION()
	void ReceiveItem(AActor* Item);
	UFUNCTION()
	void RemoveItem(AActor* Item);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
		UItemHolderComponent* HolderComp;

	virtual void BeginPlay() override;
	UGM_BargainComponent* BargainComp;
};