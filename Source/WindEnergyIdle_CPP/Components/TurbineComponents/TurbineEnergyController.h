// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TurbineEnergyController.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WINDENERGYIDLE_CPP_API UTurbineEnergyController : public UActorComponent
{
	GENERATED_BODY()

private:
	
	class AWEI_GM* GameMode;

	UPROPERTY(EditDefaultsOnly)
	float BaseEnergyPerSecond = 5;

	float Energy = 0;
	float WindMultiplier = 0;

	float PreviousEnergy = 0;
	float PreviousWindMultiplier = 0;

	float PreviewedWindMultiplier = 0;
	float PreviewedEnergy = 0;

public:
	// Sets default values for this component's properties
	UTurbineEnergyController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	float GetWindMultiplier() const;

	UFUNCTION(BlueprintCallable)
	float GetPreviousWindMultiplier() const;

	UFUNCTION(BlueprintCallable)
	void SetPreviewedEnergy(float NewWindMultiplier);

	UFUNCTION(BlueprintCallable)
	float GetPreviewedEnergy() const;

	UFUNCTION(BlueprintCallable)
	void SetEnergy();

	UFUNCTION(BlueprintCallable)
	float GetEnergy();

	void ResetEnergy() const;
};
