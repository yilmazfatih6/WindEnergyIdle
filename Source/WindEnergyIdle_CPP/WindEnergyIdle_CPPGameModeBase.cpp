// Copyright Epic Games, Inc. All Rights Reserved.


#include "WindEnergyIdle_CPPGameModeBase.h"

#include "Managers/UpgradeManager.h"
#include "WindEnergyIdle_CPP/Managers/EnergyManager.h"

AWindEnergyIdle_CPPGameModeBase::AWindEnergyIdle_CPPGameModeBase()
{
	EnergyManager = CreateDefaultSubobject<UEnergyManager>(TEXT("Energy Manager"));
	UpgradeManager = CreateDefaultSubobject<UUpgradeManager>(TEXT("Upgrade Manager"));
}
