// Fill out your copyright notice in the Description page of Project Settings.


#include "TurbinePlacementData.h"

UTurbinePlacementData::UTurbinePlacementData(): Turbine(nullptr), bIsFirstPlacement(false)
{
}

UTurbinePlacementData::UTurbinePlacementData(ATurbine* Turbine, bool bIsFirstPlacement): Turbine(Turbine), bIsFirstPlacement(bIsFirstPlacement)
{
	
}
