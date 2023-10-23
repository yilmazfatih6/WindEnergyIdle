// Fill out your copyright notice in the Description page of Project Settings.


#include "TurbineSpawner.h"

#include "WindEnergyIdle_CPP/Turbines/BaseTurbine.h"

// Sets default values for this component's properties
UTurbineSpawner::UTurbineSpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTurbineSpawner::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTurbineSpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTurbineSpawner::SetCanSpawn(bool value)
{
	bCanSpawn = value;
}

void UTurbineSpawner::SpawnTurbine(const int Level, bool &bWasSuccessful)
{
	if (!bCanSpawn)
	{
		UE_LOG(LogTemp, Log, TEXT("[UTurbineSpawner] Can not spawn a new turbine!"));
		bWasSuccessful = false;
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("[UTurbineSpawner] Spawn a new turbine!"));
	OnSpawnStart.Broadcast(SpawnedTurbine);

	bWasSuccessful = true;
	bCanSpawn = false;
	SpawnedTurbine = GetWorld()->SpawnActor<ABaseTurbine>(TurbineBlueprints[Level - 1], SpawnLocation, SpawnRotation);
	SpawnedTurbines.Add(SpawnedTurbine);

	AddToTurbinesByLevels(SpawnedTurbine, Level);

	// Raise event.
	OnSpawnComplete.Broadcast(SpawnedTurbine);
	
	// SetTurbineSelected(SpawnedTurbine);
	// UE_LOG(LogTemp, Log, TEXT("[WEI_Pawn] SpawnTurbine, Turbine: %s"), *SpawnedTurbine->GetName());
	//
	// OnTurbinePlacementStart.Broadcast();
}

void UTurbineSpawner::RemoveTurbineFromArray(ABaseTurbine* Turbine)
{
	SpawnedTurbines.Remove(Turbine);
	
	RemoveToTurbinesByLevels(Turbine);
}

void UTurbineSpawner::DespawnTurbine(ABaseTurbine* Turbine)
{
	Turbine->Destroy();
}

const TArray<TArray<ABaseTurbine*>*>* UTurbineSpawner::GetSpawnedTurbinesByLevel()  const
{
	return SpawnedTurbinesByLevel;
}

void UTurbineSpawner::AddToTurbinesByLevels(ABaseTurbine* Turbine, int Level)
{
	// Init TArray if null
	if(SpawnedTurbinesByLevel == nullptr)
	{
		SpawnedTurbinesByLevel = new TArray<TArray<ABaseTurbine*>*>();
	}

	// Add TArrays to TArray till required amount is reached.
	if(SpawnedTurbinesByLevel->Num() < Level)
	{
		while (SpawnedTurbinesByLevel->Num() < Level)
		{
			TArray<ABaseTurbine*>* NewRecord = new TArray<ABaseTurbine*>;
			SpawnedTurbinesByLevel->Add(NewRecord);
		}
	}

	// Add turbine to turbines array.
	const auto TurbinesOfThisLevel = (*SpawnedTurbinesByLevel)[Level-1];
	TurbinesOfThisLevel->Add(Turbine);
	
	UE_LOG(LogTemp, Log, TEXT("[UTurbineSpawner] AddToTurbinesByLevels, Total number of Level %d turbines is %d"), Level, TurbinesOfThisLevel->Num());
}

void UTurbineSpawner::RemoveToTurbinesByLevels(ABaseTurbine* Turbine) const
{
	for (int i = 0; i < SpawnedTurbinesByLevel->Num(); ++i)
	{
		const auto Turbines = (*SpawnedTurbinesByLevel)[i];
		if(Turbines->Contains(Turbine))
		{
			Turbines->Remove(Turbine);
			return;
		}
	}
}


