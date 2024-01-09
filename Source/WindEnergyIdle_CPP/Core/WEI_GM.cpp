// Copyright Epic Games, Inc. All Rights Reserved.


#include "WEI_GM.h"

#include "WindEnergyIdle_CPP/Managers/LevelManager.h"
#include "WindEnergyIdle_CPP/Managers/UpgradeManager.h"
#include "WindEnergyIdle_CPP/Managers/EnergyManager.h"
#include "WindEnergyIdle_CPP/Managers/ResourceManager.h"

void AWEI_GM::BeginPlay()
{
	Super::BeginPlay();
}

AWEI_GM::AWEI_GM()
{
	EnergyManager = CreateDefaultSubobject<UEnergyManager>(TEXT("Energy Manager"));
	UpgradeManager = CreateDefaultSubobject<UUpgradeManager>(TEXT("Upgrade Manager"));
	LevelManager = CreateDefaultSubobject<ULevelManager>(TEXT("Level Manager"));
	ResourceManager = CreateDefaultSubobject<UResourceManager>(TEXT("Resource Manager"));

	EnergyManager->InjectData(ResourceManager);
}
