// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TurbineDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class WINDENERGYIDLE_CPP_API UTurbineDataAsset : public UDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	float RotationMultiplier = 1;
	
	UPROPERTY(EditDefaultsOnly)
	float BoostRotationMultiplier = 1;

public:
	float GetRotationMultiplier() const;
	float GetBoostRotationMultiplier() const;
};
