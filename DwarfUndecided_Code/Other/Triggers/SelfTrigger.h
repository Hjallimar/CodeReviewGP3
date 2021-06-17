// (C) 2021 Changemaker Educations (FG20FT GP3 Team 8) - All Rights Reserved.

// AUTHOR: Justus Hörberg

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SelfTrigger.generated.h"

class UShapeComponent;

UCLASS()
class COOLGP3PROJECT_API ASelfTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASelfTrigger();

	/* The collision component that detects the collision. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UShapeComponent* CollisionComponent;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void BeginDestroy() override;

protected:
	UFUNCTION(BlueprintNativeEvent)
	void OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void OnTriggerEnter_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintNativeEvent)
	void OnTriggerExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	virtual void OnTriggerExit_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
