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
	float IncomeUpdateInterval = .5f;
	
	UPROPERTY(EditDefaultsOnly)
	float IncomePerEnergy = .00001f;
	
	UPROPERTY(EditDefaultsOnly)
	float BoostStep = .25f;
	
	UPROPERTY(EditDefaultsOnly)
	float MaxBoost = 2;

	UPROPERTY(EditDefaultsOnly)
	float BoostFadeDuration = 2;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* IncomePerSecondGraph;

public:
	float GetIncomeUpdateInterval() const;
	float GetIncomePerEnergy() const;
	float GetBoostStep() const;
	static float GetMinBoost();
	float GetMaxBoost() const;
	float GetBoostFadeDuration() const;
	UCurveFloat* GetIncomePerSecondGraph() const;
};
