// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TurbinePlacementData.generated.h"

class ATurbine;

/**
 * 
 */
UCLASS()
class WINDENERGYIDLE_CPP_API UTurbinePlacementData : public UObject
{
	GENERATED_BODY()

public:
	UTurbinePlacementData();
	UTurbinePlacementData(ATurbine* Turbine, bool bIsFirstPlacement);

	ATurbine* Turbine;
	bool bIsFirstPlacement;
};
