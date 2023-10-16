// Fill out your copyright notice in the Description page of Project Settings.


#include "TurbineSpawner.h"

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

void UTurbineSpawner::SpawnTurbine(bool &bWasSuccessful)
{
	if (!bCanSpawn)
	{
		UE_LOG(LogTemp, Log, TEXT("[TurbineSpawner] Can not spawn a new turbine!"));
		bWasSuccessful = false;
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("[TurbineSpawner] Spawn a new turbine!"));

	OnSpawnStart.Broadcast();
	
	bWasSuccessful = true;
	bCanSpawn = false;
	spawnedTurbine = GetWorld()->SpawnActor<ABaseTurbine>(TurbineToSpawn, SpawnLocation, SpawnRotation);

	// Raise event.
	OnSpawn.Broadcast(spawnedTurbine);
	
	// SetTurbineSelected(SpawnedTurbine);
	// UE_LOG(LogTemp, Log, TEXT("[WEI_Pawn] SpawnTurbine, Turbine: %s"), *SpawnedTurbine->GetName());
	//
	// OnTurbinePlacementStart.Broadcast();
}


