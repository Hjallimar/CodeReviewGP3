// (C) 2021 Changemaker Educations (FG20FT GP3 Team 8) - All Rights Reserved.

// AUTHOR: Justus Hörberg

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "AudioHandlerComponent.generated.h"

class UAudioComponent;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
/* Component that manages and plays sound on UAudioComponents for an actor and comes with various features. */
class COOLGP3PROJECT_API UAudioHandlerComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAudioHandlerComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Handler Settings")
	int AudioComponentCount = 0;

	///* The attenuation that this component will default to when no custom attenuation is used. */
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Handler Settings")
	//struct FSoundAttenuationSettings DefaultAttenuationSettings;

	/* Audio component that always exists on the component, that will be resorted to if no other audio component is available. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAudioComponent* DefaultAudioComponent;

	/* Audio components that exist for as long as this component. These will play the sounds that are being requested to play. */
	UPROPERTY(Transient)
	TArray<UAudioComponent*> AudioChannels;

	/* Returns an appropriate audio component that is currently vacant or cancellable. */
	UAudioComponent* GetAppropriateAudioComponent() const;

public:
	/* Plays a sound on this component. */
	UFUNCTION(BlueprintCallable)
	void PlaySound(USoundWave* Sound, bool bLooping = false, float Volume = 1, float Pitch = 1);

	/* Plays a sound on this component. */
	UFUNCTION(BlueprintCallable)
	void PlaySound_Attenuated(USoundWave* Sound, bool bUseCustomAttenuation, FSoundAttenuationSettings CustomAttenuation, bool bLooping = false, float Volume = 1, float Pitch = 1);
};
