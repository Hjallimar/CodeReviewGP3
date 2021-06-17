// (C) 2021 Changemaker Educations (FG20FT GP3 Team 8) - All Rights Reserved.


#include "GameSystem/PlayerMultiController.h"
#include "GameFramework/InputSettings.h"

APlayerMultiController::APlayerMultiController()
{

}

void APlayerMultiController::BeginPlay()
{
	Super::BeginPlay();

	SetupInput();
}

void APlayerMultiController::SetupInactiveStateInputComponent(UInputComponent* InComponent)
{
	Super::SetupInactiveStateInputComponent(InComponent);

	//check(InComponent);

	//InComponent->BindAction("Confirm", IE_Pressed, this, &APlayerMultiController::OnInputConfirm);
	//InComponent->BindAction("Menu", IE_Pressed, this, &APlayerMultiController::OnInputMenu);
	//InComponent->BindAction("NextPage", IE_Released, this, &APlayerMultiController::OnInputNextPage);
	//InComponent->BindAction("PreviousPage", IE_Released, this, &APlayerMultiController::OnInputPreviousPage);
	//InComponent->BindAction("Confirm", IE_Pressed, this, &APlayerMultiController::OnInputConfirm);
	//InComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::InteractWithItem); //JL
	//InComponent->BindAction("Break", IE_Pressed, this, &APlayerCharacter::BreakInteract);
}

void APlayerMultiController::OnActionConfirm()
{
	OnConfirm.Broadcast();
}

void APlayerMultiController::OnActionNextPage()
{
	OnNextPage.Broadcast();
}

void APlayerMultiController::OnActionPreviousPage()
{
	OnPreviousPage.Broadcast();
}

void APlayerMultiController::OnActionMenu()
{
	OnMenu.Broadcast();
}

void APlayerMultiController::OnActionInteract()
{
	OnInteract.Broadcast();
}

void APlayerMultiController::OnActionEndDay()
{
	OnEndDay.Broadcast();
}

void APlayerMultiController::OnActionBreak()
{
	OnBreak.Broadcast();
}

void APlayerMultiController::OnActionOpenTaskList()
{
	OnOpenTaskList.Broadcast();
}

void APlayerMultiController::OnAxisMoveForward(float Value)
{
	//UE_LOG(LogTemp, Log, TEXT("ddd %f"), Value);
	OnMoveForward.Broadcast(Value);
}

void APlayerMultiController::OnAxisMoveRight(float Value)
{
	OnMoveRight.Broadcast(Value);
}

void APlayerMultiController::OnAxisLookUp(float Value)
{
	OnLookUp.Broadcast(Value);
}

void APlayerMultiController::OnAxisLookRight(float Value)
{
	OnLookRight.Broadcast(Value);
}

void APlayerMultiController::SetupInput()
{
	EnableInput(this);

	check(InputComponent);

	InputComponent->BindAction("Confirm", IE_Pressed, this, &APlayerMultiController::OnActionConfirm);
	InputComponent->BindAction("Menu", IE_Pressed, this, &APlayerMultiController::OnActionMenu);
	InputComponent->BindAction("NextPage", IE_Released, this, &APlayerMultiController::OnActionNextPage);
	InputComponent->BindAction("PreviousPage", IE_Released, this, &APlayerMultiController::OnActionPreviousPage);
	InputComponent->BindAction("Menu", IE_Pressed, this, &APlayerMultiController::OnActionMenu);
	InputComponent->BindAction("Interact", IE_Pressed, this, &APlayerMultiController::OnActionInteract);
	InputComponent->BindAction("EndDay", IE_Pressed, this, &APlayerMultiController::OnActionEndDay);
	InputComponent->BindAction("Break", IE_Pressed, this, &APlayerMultiController::OnActionBreak);
	InputComponent->BindAction("OpenTaskList", IE_Pressed, this, &APlayerMultiController::OnActionOpenTaskList);

	InputComponent->BindAxis("MoveForward", this, &APlayerMultiController::OnAxisMoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerMultiController::OnAxisMoveRight);
	InputComponent->BindAxis("LookUp", this, &APlayerMultiController::OnAxisLookUp);
	InputComponent->BindAxis("LookRight", this, &APlayerMultiController::OnAxisLookRight);
}
