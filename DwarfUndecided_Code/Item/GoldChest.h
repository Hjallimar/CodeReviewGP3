//Author Johan Liljedahl

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "GameFramework/Actor.h"
#include "GameSystem/GP3GameMode.h"
#include "UI/HUD/GameHUD.h"
#include "GoldChest.generated.h"

class UStaticMeshComponent;
class UInteractableComponent;
class ABaseItem;

UCLASS()
class COOLGP3PROJECT_API AGoldChest : public AActor
{
	GENERATED_BODY()
	
public:	
	AGoldChest();
	virtual void Tick(float DeltaTime) override;
	void AddGold(int Value);
	void RemoveGold(int Value);

	UFUNCTION(BlueprintImplementableEvent)
	void OnGoldAdded();
	UFUNCTION(BlueprintImplementableEvent)
	void OnGoldRemoved();
	UFUNCTION(BlueprintCallable)
	void OnPlayerHover(AActor* Player);
	UFUNCTION(BlueprintCallable)
    void OnPlayerStopHover(AActor* Player);
	FDisplayLabelData GenerateDisplayItemInfo();
	int GetCurrentGold();
	void UpdateGoldInStorage();
protected:
	virtual void BeginPlay() override;
	void CheckIfMeshShouldChange();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInteractableComponent* Interactable;
	AGP3GameMode* MyGameMode;
	AGameHUD* MyGameHUD;
	
	int GoldInStorage = 0;
	UPROPERTY(EditAnywhere)
	TArray<UStaticMesh*> Meshes;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Transform;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
	int ValueForEmpty;
	UPROPERTY(EditAnywhere)
	int ValueForPoor;
	UPROPERTY(EditAnywhere)
	int ValueForNormal;
	//UPROPERTY(EditAnywhere)
	//int ValueForRich;
	
};
