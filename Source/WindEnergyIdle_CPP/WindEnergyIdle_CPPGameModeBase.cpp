// Copyright Epic Games, Inc. All Rights Reserved.


#include "WindEnergyIdle_CPPGameModeBase.h"

#include "Managers/LevelManager.h"
#include "Managers/UpgradeManager.h"
#include "WindEnergyIdle_CPP/Managers/EnergyManager.h"

void AWindEnergyIdle_CPPGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

AWindEnergyIdle_CPPGameModeBase::AWindEnergyIdle_CPPGameModeBase()
{
	EnergyManager = CreateDefaultSubobject<UEnergyManager>(TEXT("Energy Manager"));
	UpgradeManager = CreateDefaultSubobject<UUpgradeManager>(TEXT("Upgrade Manager"));
	LevelManager = CreateDefaultSubobject<ULevelManager>(TEXT("Level Manager"));
}
