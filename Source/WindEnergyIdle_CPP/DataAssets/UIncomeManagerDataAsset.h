// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UIncomeManagerDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class WINDENERGYIDLE_CPP_API UUIncomeManagerDataAsset : public UDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	float IncomePerEnergy = .00001f;
	
	UPROPERTY(EditDefaultsOnly)
	float BoostStep = .25f;
	
	UPROPERTY(EditDefaultsOnly)
	float MaxBoost = 2;

	UPROPERTY(EditDefaultsOnly)
	float BoostFadeDuration = 2;

public:
	float GetIncomePerEnergy() const;
	float GetBoostStep() const;
	float GetMaxBoost() const;
	float GetBoostFadeDuration() const;
};
