// (C) 2021 Changemaker Educations (FG20FT GP3 Team 8) - All Rights Reserved.

// AUTHOR: Justus Hörberg

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameSound/SoundRelated.h"
#include "FootstepComponent.generated.h"

class UAudioComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COOLGP3PROJECT_API UFootstepComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UFootstepComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

	virtual void PlayFootstepSound(const EFootstepType FootstepType);

	UFUNCTION()
	void OnGroundStateChanged(const bool OnGround, const bool PreviouslyOnGround);


	bool bCanCurrentlyPlaySounds;

	/* The index of the footstep that will play. Normally, all footsteps play in the order they were put in the FootstepSounds array. */
	int FootstepPlayIndex;
	
	/* Value that decreases when moving, by the position delta. When it reaches 0, a footstep sound plays, and is then reset to FootstepDistance. */
	float FootstepTimer;

	/* The position on the previous frame. Used as part of distance calculation. */
	FVector PreviousPosition;
	
	/* The audio component that will emit the footstep sounds. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAudioComponent* FootstepEmitter;

	/* Whether or not this component should play footstep sounds. */
	UPROPERTY(EditAnywhere)
	bool bCanPlaySounds = true;

	/* The distance in Unreal units that this component has to travel in world space to emit a footstep sound. */
	UPROPERTY(EditAnywhere, meta = (ClampMin = "1.0"))
	float FootstepDistance = 1.f;
	
	/* The sounds that will play when a distance has been walked on wood. */
	UPROPERTY(EditAnywhere)
		TArray<USoundWave*> FootstepSounds_Wood;

	/* The sounds that will play when a distance has been walked on concrete. */
	UPROPERTY(EditAnywhere)
		TArray<USoundWave*> FootstepSounds_Concrete;

	/* Contains pointers to arrays that contain sounds that play based on what type of surface the player stands on. */
	TMap<EFootstepType, const TArray<USoundWave*>*> FootstepSoundArrayPointers;

public:
	/* Returns the distance travelled between the current and last frame. */
	UFUNCTION(BlueprintCallable)
		float GetPositionDelta() const;
	
	/* Returns the squared distance travelled between the current and last frame. Costs less in performance. */
	UFUNCTION(BlueprintCallable)
		float GetSquaredPositionDelta() const;
};
