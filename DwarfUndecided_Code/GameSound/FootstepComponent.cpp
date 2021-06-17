// (C) 2021 Changemaker Educations (FG20FT GP3 Team 8) - All Rights Reserved.

#include "GameSound/FootstepComponent.h"
#include "CustomComponents/Movement/GeneralMovementComponent.h"
#include "Components/AudioComponent.h"

UFootstepComponent::UFootstepComponent()
{
	// No tick if no sound :)
	PrimaryComponentTick.bCanEverTick = true;//FootstepSounds.Num() > 0;

	AActor* Owner = GetOwner();
	FootstepEmitter = CreateDefaultSubobject<UAudioComponent>("Footstep Emitter");
	FootstepEmitter->SetupAttachment(this);
}


void UFootstepComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (Owner)
	{
		// Find an appropriate audio component to play sounds on.
		UAudioComponent* AudioComponent = Owner->FindComponentByClass<UAudioComponent>();
		if (AudioComponent)
		{
			FootstepEmitter = AudioComponent;
		}
		else
		{
			FootstepEmitter = Owner->CreateDefaultSubobject<UAudioComponent>("Footstep Emitter");
		}

		//if (!FootstepEmitter->GetAttachParent())
		//{
		//	//FAttachmentTransformRules AttachmentRules;
		//	//FootstepEmitter->AttachToComponent(this, AttachmentRules);
		//}

		UGeneralMovementComponent* MoveComponent = Owner->FindComponentByClass<UGeneralMovementComponent>();
		if (MoveComponent)
		{
			MoveComponent->OnGroundStateChanged.AddDynamic(this, &UFootstepComponent::OnGroundStateChanged);
		}

		PreviousPosition = GetOwner()->GetActorLocation();
	}

	bCanCurrentlyPlaySounds = true;

	// Assign the pointers to the sound collections
	FootstepSoundArrayPointers = TMap<EFootstepType, const TArray<USoundWave*>*>
	{
		{ EFootstepType::Wood, &FootstepSounds_Wood },
		{ EFootstepType::Concrete, &FootstepSounds_Concrete },
	};
	
	FootstepTimer = FootstepDistance/* * FootstepDistance*/;
}

void UFootstepComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	AActor* Owner = GetOwner();
	if (Owner)
	{
		UGeneralMovementComponent* MoveComponent = Owner->FindComponentByClass<UGeneralMovementComponent>();
		if (MoveComponent)
		{
			MoveComponent->OnGroundStateChanged.RemoveDynamic(this, &UFootstepComponent::OnGroundStateChanged);
		}
	}
	
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}

void UFootstepComponent::PlayFootstepSound(const EFootstepType FootstepType)
{
	if (FootstepEmitter && FootstepSoundArrayPointers.Contains(FootstepType))
	{
		const TArray<USoundWave*>* SoundArray = FootstepSoundArrayPointers[FootstepType];
		if (SoundArray && SoundArray->Num() > 0)
		{
			if (FootstepPlayIndex >= SoundArray->Num())
				FootstepPlayIndex = 0;

			USoundWave* Sound = (*SoundArray)[FootstepPlayIndex];
			if (Sound)
			{
				FootstepEmitter->Sound = Sound;
				FootstepEmitter->Play();
			}

			FootstepPlayIndex++;
		}
	}
}

void UFootstepComponent::OnGroundStateChanged(const bool OnGround, const bool PreviouslyOnGround)
{
	bCanCurrentlyPlaySounds = OnGround;
}

float UFootstepComponent::GetPositionDelta() const
{
	AActor* Owner = GetOwner();
	if (Owner)
	{
		return (Owner->GetActorLocation() - PreviousPosition).Size();
	}

	return 0;
}

float UFootstepComponent::GetSquaredPositionDelta() const
{
	AActor* Owner = GetOwner();
	if (Owner)
	{
		return (Owner->GetActorLocation() - PreviousPosition).SizeSquared();
	}

	return 0;
}

void UFootstepComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const float ThisFrameDelta = GetSquaredPositionDelta();
	
	if (!bCanPlaySounds || !bCanCurrentlyPlaySounds || !FootstepEmitter ||
		FootstepSoundArrayPointers.Num() <= 0 || ThisFrameDelta == 0)
	{
		//FString Reason;
		//if (!bCanPlaySounds)
		//	Reason = TEXT("bCanPlaySounds is false");
		//else if (!bCanCurrentlyPlaySounds)
		//	Reason = TEXT("bCanCurrentlyPlaySounds is false");
		//else if (!FootstepEmitter)
		//	Reason = TEXT("FootstepEmitter is nullptr");
		//else if (FootstepSoundArrayPointers.Num() <= 0)
		//	Reason = TEXT("FootstepSoundArrayPointers Length is 0");
		//else if (ThisFrameDelta == 0)
		//	Reason = TEXT("ThisFrameDelta is 0");
		//else
		//	Reason = TEXT("Fuck you, I won't do what you tell me :)");

		//UE_LOG(LogTemp, Log, TEXT("%s"), *Reason);
			
		return;
	}

	FootstepTimer -= FMath::Sqrt(ThisFrameDelta);

	if (FootstepTimer <= 0)
	{
		// @TODO: Implement footstep recognition
		EFootstepType FootstepType = EFootstepType::Wood;

		PlayFootstepSound(FootstepType);
		
		// Avoidin' sqrt
		FootstepTimer = FootstepDistance;
	}

	PreviousPosition = GetOwner()->GetActorLocation();
}

