// Fill out your copyright notice in the Description page of Project Settings.


#include "TurbineMerger.h"

#include "TurbinePlacer.h"
#include "WindEnergyIdle_CPP/TurbineBlueprintData.h"
// #include "WindEnergyIdle_CPP/TurbineEnergyController.h"
#include "TurbineSelector.h"
#include "WindEnergyIdle_CPP/TurbineEnergyController.h"
#include "WindEnergyIdle_CPP/Turbines/BaseTurbine.h"

UTurbineMerger::UTurbineMerger()
{
	UE_LOG(LogTemp, Log, TEXT("[UTurbineMerger] UTurbineMerger"));

	ClosestTurbines = new TArray<ABaseTurbine*>;
}

// Sets default values for this component's properties
void UTurbineMerger::InjectData(UTurbineSpawner* TurbineSpawnerReference, UTurbinePlacer* TurbinePlacerReference, UTurbineSelector* TurbineSelectorReference)
{
	UE_LOG(LogTemp, Log, TEXT("[UTurbineMerger] InjectData"));

	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	TurbineSpawner = TurbineSpawnerReference;
	TurbinePlacer = TurbinePlacerReference;
	TurbineSelector = TurbineSelectorReference;

	UE_LOG(LogTemp, Log, TEXT("[UTurbineMerger] InjectData, TurbineSpawner: %s"), *TurbineSpawner->GetName());
	TurbineSpawner->OnSpawnComplete.AddDynamic(this, &ThisClass::OnTurbineSpawn);
}


// Called when the game starts
void UTurbineMerger::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("[UTurbineMerger] BeginPlay"));
}


// Called every frame
void UTurbineMerger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTurbineMerger::Merge()
{
	UE_LOG(LogTemp, Log, TEXT("[UTurbineMerger] Merge"));
	
	if(TurbineSpawner == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UTurbineMerger] Merge, TurbineSpawner is null!"));
		return;
	}

	if(TurbineSpawner->GetSpawnedTurbinesByLevel() == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UTurbineMerger] Merge, SpawnedTurbinesByLevel is null!"));
		return;
	}
	
	ClosestTurbines->Empty();

	// Get turbines to merge!
	for (int i = TurbineSpawner->GetSpawnedTurbinesByLevel()->Num() - 1; i >= 0 ; i--)
	{
		// Store turbines in a local variable.
		const auto Turbines = (*TurbineSpawner->GetSpawnedTurbinesByLevel())[i];
		
		// Skip if this turbines are max level.
		const auto TurbinesLevel = i + 1;
		const auto MaxTurbineLevel = TurbineSpawner->GetTurbineBlueprints()->Turbines.Num();
		UE_LOG(LogTemp, Warning, TEXT("[UTurbineMerger] TurbinesLevel=%d"), TurbinesLevel)
		UE_LOG(LogTemp, Warning, TEXT("[UTurbineMerger] MaxTurbineLevel=%d"), MaxTurbineLevel)
		
		if(TurbinesLevel == MaxTurbineLevel) continue;

		// Skip if number of turbines in this level is less than required amount
		if(Turbines->Num() < MERGE_TURBINE_AMOUNT) continue;

		bool bWasSuccessful = false;
		FindClosestObjects(Turbines, bWasSuccessful);
		if(bWasSuccessful) break;
	}

	UE_LOG(LogTemp, Warning, TEXT("[UTurbineMerger] Merge, ClosestTurbines->Num()=%d"), ClosestTurbines->Num());

	// Return if there is not enough turbines to merge.
	if(ClosestTurbines->Num() < MERGE_TURBINE_AMOUNT)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UTurbineMerger] Merge, Not enough ClosestTurbines!"));
		return;
	}

	// Detect which turbine has max wind multiplier.
	auto CenterTurbineIndex = -1.f;
	auto MaxWindMultiplier = -1.f;
	for (int i = 0; i < ClosestTurbines->Num(); ++i)
	{
		const auto WindMultiplier = 1; //(*ClosestTurbines)[i]->GetEnergyController()->GetWindMultiplier();
		if(WindMultiplier <= MaxWindMultiplier) continue;

		CenterTurbineIndex = i;
		MaxWindMultiplier = WindMultiplier;
	}

	// Finally Merge!
	CenterTurbine = (*ClosestTurbines)[CenterTurbineIndex];
	CenterTurbineWindMultiplier = CenterTurbine->GetEnergyController()->GetWindMultiplier();
	for (int i = 0; i < ClosestTurbines->Num(); ++i)
	{
		const auto Turbine = (*ClosestTurbines)[i];
		if(i != CenterTurbineIndex)
		{
			Turbine->StartMovement(CenterTurbine->GetActorLocation());
			Turbine->OnMovementComplete.AddDynamic(this, &ThisClass::OnMergeMovementComplete);
		}
		TurbineSpawner->RemoveTurbineFromArray(Turbine);
	}
}

void UTurbineMerger::OnTurbineSpawn(ABaseTurbine* Turbine)
{
	// UE_LOG(LogTemp, Log, TEXT("[UTurbineMerger] OnTurbineSpawn"));
	// SetCanMerge();
}

void UTurbineMerger::SetCanMerge()
{
	UE_LOG(LogTemp, Log, TEXT("[UTurbineMerger] SetCanMerge"));

	if(TurbineSpawner == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("[UTurbineMerger] SetCanMerge, TurbineSpawner is null!"));
		return;
	}

	bCanMerge = false;

	const auto SpawnedTurbinesByLevel = TurbineSpawner->GetSpawnedTurbinesByLevel();
	
	for (int i = 0; i < SpawnedTurbinesByLevel->Num(); i++)
	{
		const auto SpawnedTurbines = (*SpawnedTurbinesByLevel)[i];
		
		if(SpawnedTurbines->Num() >= MERGE_TURBINE_AMOUNT)
		{
			bCanMerge = true;
			return;
		}
	}
}

void UTurbineMerger::FindClosestObjects(TArray<ABaseTurbine*>* Turbines, bool& bWasSuccessful) const
{
	bWasSuccessful = false;
	
	// Return if turbine count is less than MERGE_TURBINE_AMOUNT.
	const int32 NumObjects = Turbines->Num();
	if (NumObjects < MERGE_TURBINE_AMOUNT)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UTurbineMerger] There are not enough objects in the list to find the closest three objects."));
		return;
	}

	float ClosestDistance = TNumericLimits<float>::Max();
	
	for (int32 i = 0; i < NumObjects - 2; i++)
	{
		ABaseTurbine* ObjectA = (*Turbines)[i];
		
		for (int32 j = i + 1; j < NumObjects - 1; j++)
		{
			ABaseTurbine* ObjectB = (*Turbines)[j];
			const float DistanceAB = FVector::Distance(ObjectA->GetActorLocation(), ObjectB->GetActorLocation());
	
			for (int32 k = j + 1; k < NumObjects; k++)
			{
				ABaseTurbine* ObjectC = (*Turbines)[k];
				FVector Position = ObjectC->GetActorLocation();
				const float DistanceAC = FVector::Distance(ObjectA->GetActorLocation(), Position);
				const float DistanceBC = FVector::Distance(ObjectB->GetActorLocation(), Position);
				const float MaxDistance = FMath::Max3(DistanceAB, DistanceAC, DistanceBC);
	
				if (MaxDistance >= ClosestDistance)
				{
					continue;
				}
	
				ClosestDistance = MaxDistance;
				ClosestTurbines->Empty();
				ClosestTurbines->Add(ObjectA);
				ClosestTurbines->Add(ObjectB);
				ClosestTurbines->Add(ObjectC);
			}                    
		}
	}
	
	bWasSuccessful = true;
}

void UTurbineMerger::OnMergeMovementComplete(ABaseTurbine* Turbine)
{
	UE_LOG(LogTemp, Log, TEXT("[UTurbineMerger] OnMergeMovementComplete"));
	Turbine->OnMovementComplete.RemoveDynamic(this, &ThisClass::OnMergeMovementComplete);
	MergeMovementCompleteCount++;

	// Check if all movement completed.
	if(MergeMovementCompleteCount == MERGE_TURBINE_AMOUNT - 1)
	{
		// Reset counter.
		MergeMovementCompleteCount = 0;
		
		const auto FirstClosestTurbine = (*ClosestTurbines)[0];
		
		// Despawn previous turbines
		for (int i = 0; i < ClosestTurbines->Num(); ++i)
		{
			const auto CurrentTurbine = (*ClosestTurbines)[i];
			CurrentTurbine->GetEnergyController()->ResetEnergy();
			TurbineSpawner->DespawnTurbine(CurrentTurbine);
		}

		// Spawn next level turbine
		const auto TurbineLevel = FirstClosestTurbine->GetLevel();
		const auto NextTurbineLevel = TurbineLevel + 1;
		bool bWasSuccessful = false;
		const auto SpawnedTurbine = TurbineSpawner->SpawnTurbine(NextTurbineLevel, bWasSuccessful);

		// Set location
		SpawnedTurbine->SetActorLocation(CenterTurbine->GetActorLocation());

		// Place

		if(TurbinePlacer == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("[TurbineMerger] OnMergeMovementComplete TurbinePlacer is null!"));
			return;
		}

		TurbineSelector->GetSelectedTurbine()->GetEnergyController()->SetPreviewedEnergy(CenterTurbineWindMultiplier);
		TurbinePlacer->Place();
	}
}
