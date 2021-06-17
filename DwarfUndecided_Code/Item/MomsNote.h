// (C) 2021 Changemaker Educations (FG20FT GP3 Team 8) - All Rights Reserved.
// AUTHOR: Justus Hörberg

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MomsNote.generated.h"

class UInteractableComponent;
class UStaticMeshComponent;

UCLASS()
class COOLGP3PROJECT_API AMomsNote : public AActor
{
	GENERATED_BODY()
	
public:	
	AMomsNote();

protected:
	/* The interactable component that allows the note to be interacted with. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UInteractableComponent* InteractableComponent;

	/* The base mesh of the actor. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;

	/* The highlight mesh of the actor. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* OverlayMesh;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
