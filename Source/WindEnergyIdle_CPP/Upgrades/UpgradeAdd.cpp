// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeAdd.h"

#include "WindEnergyIdle_CPP/Components/PawnComponents/TurbineSpawner.h"

void UUpgradeAdd::Use()
{
	Super::Use();
	
	if(!CanUse) return;

	if(Pawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[UUpgradeAdd] Use(), Pawn is null!"));
		return;
	}
	
	const auto TurbineSpawner = Pawn->GetTurbineSpawner();
	if(TurbineSpawner == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[UUpgradeAdd] Use(), TurbineSpawner is null!"));
		return;
	}

	bool bWasSuccessful;
	TurbineSpawner->SpawnTurbine(1, bWasSuccessful);

	if(bWasSuccessful == false)
	{
		UE_LOG(LogTemp, Error, TEXT("[UUpgradeAdd] Use(), SpawnTurbine was not successful!"));
		return;
	}
}
