// (C) 2021 Changemaker Educations (FG20FT GP3 Team 8) - All Rights Reserved.

// AUTHOR: Justus Hörberg

#include "GameSound/AudioHandlerComponent.h"
#include "Components/AudioComponent.h"

// Sets default values for this component's properties
UAudioHandlerComponent::UAudioHandlerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;
	if (!DefaultAudioComponent)
	{
		DefaultAudioComponent = CreateDefaultSubobject<UAudioComponent>("Default Audio");
		DefaultAudioComponent->SetupAttachment(this);
	}
}


// Called when the game starts
void UAudioHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AudioComponentCount > 0)
	{
		AActor* Owner = GetOwner();
		if (Owner)
		{
			for (int Index = 0; Index < AudioComponentCount; Index++)
			{
				FName ComponentName = "AudioChannel " + Index;
				UAudioComponent* CreatedComp = NewObject<UAudioComponent>(this, UAudioComponent::StaticClass(), ComponentName);
				if (CreatedComp)
				{
					CreatedComp->RegisterComponent();
					FAttachmentTransformRules Attach(EAttachmentRule::SnapToTarget, false);
					CreatedComp->AttachToComponent(Owner->GetRootComponent(), Attach);
					AudioChannels.Add(CreatedComp);
				}
			}
		}
	}

}

void UAudioHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Currently not supposed to tick!
}

UAudioComponent* UAudioHandlerComponent::GetAppropriateAudioComponent() const
{
	for (UAudioComponent* AudioComponent : AudioChannels)
	{
		if (AudioComponent && !AudioComponent->IsPlaying())
		{
			return AudioComponent;
		}
	}

	return DefaultAudioComponent;
}

void UAudioHandlerComponent::PlaySound_Attenuated(USoundWave* Sound, bool bUseCustomAttenuation, FSoundAttenuationSettings CustomAttenuation, bool bLooping, float Volume, float Pitch)
{
	UAudioComponent* Audio = GetAppropriateAudioComponent();
	if (!Audio) return;

	if (!Sound) return;
	USoundWave* SoundWave = Sound;//Cast<USoundWave>(Sound->GetDefaultObject());
	if (!SoundWave) return;

	Audio->Sound = SoundWave;
	Audio->VolumeMultiplier = Volume;
	Audio->PitchMultiplier = Pitch;
	Audio->bOverrideAttenuation = bUseCustomAttenuation;
	if (Audio->bOverrideAttenuation)
	{
		Audio->AttenuationOverrides = CustomAttenuation;
	}

	Audio->Play();
}

void UAudioHandlerComponent::PlaySound(USoundWave* Sound, bool bLooping, float Volume, float Pitch)
{
	FSoundAttenuationSettings Att;
	if (DefaultAudioComponent)
	{
		Att = DefaultAudioComponent->AttenuationOverrides;
	}

	PlaySound_Attenuated(Sound, false, Att, bLooping, Volume, Pitch);
}

