// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TurbineEnergyController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WINDENERGYIDLE_CPP_API UTurbineEnergyController : public UActorComponent
{
	GENERATED_BODY()

	class AWindEnergyIdle_CPPGameModeBase* GameMode;

	UPROPERTY(EditDefaultsOnly)
	float BaseEnergyPerSecond = 5;
	float WindMultiplier = 0;
	float PreviousWindMultiplier = 0;

public:	
	// Sets default values for this component's properties
	UTurbineEnergyController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float GetWindMultiplier() const;

	void SetEnergy(float NewWindMultiplier);
	void ResetEnergy() const;
};
