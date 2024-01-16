// Copyright Epic Games, Inc. All Rights Reserved.


#include "WEI_GM.h"

#include "Kismet/GameplayStatics.h"
#include "WindEnergyIdle_CPP/Managers/LevelManager.h"
#include "WindEnergyIdle_CPP/Managers/UpgradeManager.h"
#include "WindEnergyIdle_CPP/Managers/EnergyManager.h"
#include "WindEnergyIdle_CPP/Managers/IncomeManager.h"
#include "WindEnergyIdle_CPP/Managers/ResourceManager.h"

void AWEI_GM::BeginPlay()
{
	Super::BeginPlay();

	const auto Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if(Pawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[AWEI_GM] BeginPlay, Pawn is null!"));
		return;
	}
	
	const auto WEI_Pawn = Cast<AWEI_Pawn>(Pawn);
	if(WEI_Pawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[AWEI_GM] BeginPlay, WEI_Pawn is null!"));
		return;
	}
	
	IncomeManager->InjectData(ResourceManager, EnergyManager, UpgradeManager, WEI_Pawn);
	UpgradeManager->InjectData(ResourceManager);
}

AWEI_GM::AWEI_GM()
{
	EnergyManager = CreateDefaultSubobject<UEnergyManager>(TEXT("Energy Manager"));
	UpgradeManager = CreateDefaultSubobject<UUpgradeManager>(TEXT("Upgrade Manager"));
	LevelManager = CreateDefaultSubobject<ULevelManager>(TEXT("Level Manager"));
	ResourceManager = CreateDefaultSubobject<UResourceManager>(TEXT("Resource Manager"));
	IncomeManager = CreateDefaultSubobject<UIncomeManager>(TEXT("Income Manager"));
}
