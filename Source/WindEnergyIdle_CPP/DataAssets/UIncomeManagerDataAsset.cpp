// Fill out your copyright notice in the Description page of Project Settings.


#include "UIncomeManagerDataAsset.h"

float UUIncomeManagerDataAsset::GetIncomeUpdateInterval() const
{
	return IncomeUpdateInterval;
}

inline float UUIncomeManagerDataAsset::GetIncomePerEnergy() const
{
	return IncomePerEnergy;
}

float UUIncomeManagerDataAsset::GetBoostStep() const
{
	return BoostStep;
}

float UUIncomeManagerDataAsset::GetMaxBoost() const
{
	return MaxBoost;
}

float UUIncomeManagerDataAsset::GetBoostFadeDuration() const
{
	return BoostFadeDuration;
}
