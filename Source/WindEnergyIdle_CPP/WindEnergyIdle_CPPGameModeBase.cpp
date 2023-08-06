// Copyright Epic Games, Inc. All Rights Reserved.


#include "WindEnergyIdle_CPPGameModeBase.h"

#include "EnergyManager.h"

AWindEnergyIdle_CPPGameModeBase::AWindEnergyIdle_CPPGameModeBase()
{
	EnergyManager = CreateDefaultSubobject<UEnergyManager>(TEXT("Energy Manager"));
}
