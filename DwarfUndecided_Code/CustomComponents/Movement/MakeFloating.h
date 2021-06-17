//Author Johan Liljedahl
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MakeFloating.generated.h"

class AActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COOLGP3PROJECT_API UMakeFloating : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMakeFloating();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Active;
	
protected:
	virtual void BeginPlay() override;
	AActor* Owner;
	float Value = 1;
	UPROPERTY(EditAnywhere)
	float RotationSpeed = 10;
	UPROPERTY(EditAnywhere)
	float Height = 10.f;
	UPROPERTY(EditAnywhere)
	float Speed = 1.f;
	
	void MakeFloat(float);
	void MakeRotate(float);
};
