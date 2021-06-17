//Author Olof Wallentin - Hazelight
//This class was taken from one of his courses and additions to the original code will be documented
//Class, function and variables may have their names changed without documentation

#include "FpsPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "CustomComponents/Movement/FpsMovementComponent.h"
#include "CustomComponents/Movement/FpsMovementStatics.h"
#include "Kismet/KismetSystemLibrary.h"

AFpsPlayerController::AFpsPlayerController()
{
	PrimaryActorTick.bStartWithTickEnabled = true;

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;
	Capsule->SetCollisionProfileName("BlockAllDynamic");
	Capsule->InitCapsuleSize(55.f, 96.0f);

	BaseTurnRate = 2.5f;
	BaseLookUpRate = 2.5f;

	Speed = 1000.0f;
	Gravity = 900.0f;

	FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FPSCamera->SetupAttachment(Capsule);
	FPSCamera->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f));
	FPSCamera->bUsePawnControlRotation = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	Mesh->SetOnlyOwnerSee(true);
	Mesh->SetupAttachment(FPSCamera);
	Mesh->bCastDynamicShadow = false;
	Mesh->CastShadow = false;
	Mesh->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	MovementComponent = CreateDefaultSubobject<UFpsMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->SetUpdatedComponent(Capsule);
}

void AFpsPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FFpsMovementStatics FrameMovement = MovementComponent->CreateFrameMovement();

	FrameMovement.AddGravity(Gravity * DeltaTime);

	if (!InputVector.IsNearlyZero())
	{
		FVector Forward = FVector::VectorPlaneProject(FPSCamera->GetForwardVector(), FVector::UpVector);
		FVector ForwardMovement = Forward * InputVector.X;
		FVector Right = FPSCamera->GetRightVector() * InputVector.Y;
		FVector Velocity = (ForwardMovement + Right).GetSafeNormal() * Speed * DeltaTime;
		FrameMovement.AddDelta(Velocity);
	}

	MovementComponent->Move(FrameMovement);
}

UCameraComponent* AFpsPlayerController::ReturnFPSCamera()
{
	return FPSCamera;
}

void AFpsPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AFpsPlayerController::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AFpsPlayerController::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFpsPlayerController::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AFpsPlayerController::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &AFpsPlayerController::LookUpAtRate);
}

void AFpsPlayerController::MoveForward(float Value)
{
	InputVector.X = Value;
}
void AFpsPlayerController::MoveRight(float Value)
{
	InputVector.Y = Value;
}
void AFpsPlayerController::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate);
}
void AFpsPlayerController::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate);
}
