// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeMerge.h"

#include "WindEnergyIdle_CPP/Components/PawnComponents/TurbineMerger.h"

void UUpgradeMerge::Use()
{
	Super::Use();
	
	if(!CanUse) return;

	if(Pawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[UUpgradeMerge] Use(), Pawn is null!"));
		return;
	}
	
	const auto TurbineMerger = Pawn->GetTurbineMerger();
	if(TurbineMerger == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[UUpgradeMerge] Use(), TurbineMerger is null!"));
		return;
	}

	TurbineMerger->Merge();
}
