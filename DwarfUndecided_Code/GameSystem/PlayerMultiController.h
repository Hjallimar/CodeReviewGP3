// (C) 2021 Changemaker Educations (FG20FT GP3 Team 8) - All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerMultiController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMultiActionInput);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMultiAxisInput, float, Value);

/**
 * 
 */
UCLASS()
class COOLGP3PROJECT_API APlayerMultiController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APlayerMultiController();

	FOnMultiActionInput OnConfirm;
	FOnMultiActionInput OnNextPage;
	FOnMultiActionInput OnPreviousPage;
	FOnMultiActionInput OnMenu;
	FOnMultiActionInput OnInteract;
	FOnMultiActionInput OnEndDay;
	FOnMultiActionInput OnBreak;
	FOnMultiActionInput OnOpenTaskList;

	FOnMultiAxisInput OnMoveForward;
	FOnMultiAxisInput OnMoveRight;
	FOnMultiAxisInput OnLookUp;
	FOnMultiAxisInput OnLookRight;

protected:

	//UPROPERTY(Transient)
	/* The InputComponent that executes the multicast inputs. */
	//UInputComponent* MulticastInputComponent;

	virtual void BeginPlay() override;
	virtual void SetupInactiveStateInputComponent(UInputComponent* InComponent) override;

	UFUNCTION()
	virtual void OnActionConfirm();
	UFUNCTION()
	virtual void OnActionNextPage();
	UFUNCTION()
	virtual void OnActionPreviousPage();
	UFUNCTION()
	virtual void OnActionMenu();
	UFUNCTION()
	virtual void OnActionInteract();
	UFUNCTION()
	virtual void OnActionEndDay();
	UFUNCTION()
	virtual void OnActionBreak();
	UFUNCTION()
	virtual void OnActionOpenTaskList();

	UFUNCTION()
	virtual void OnAxisMoveForward(float Value);
	UFUNCTION()
	virtual void OnAxisMoveRight(float Value);
	UFUNCTION()
	virtual void OnAxisLookUp(float Value);
	UFUNCTION()
	virtual void OnAxisLookRight(float Value);

	virtual void SetupInput();
};
