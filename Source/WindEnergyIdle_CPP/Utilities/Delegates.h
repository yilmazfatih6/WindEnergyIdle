// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WindEnergyIdle_CPP/DataContainers/TurbinePlacementData.h"
#include "Delegates.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTurbineDelegate, ATurbine*, Turbine);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTurbinePlacementDelegate, UTurbinePlacementData*, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVoidDelegate);

/**
 * 
 */
UCLASS()
class WINDENERGYIDLE_CPP_API UDelegates : public UObject
{
	GENERATED_BODY()
};
