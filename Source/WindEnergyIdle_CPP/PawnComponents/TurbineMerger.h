// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurbineSpawner.h"
#include "Components/ActorComponent.h"
#include "TurbineMerger.generated.h"


class ABaseTurbine;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WINDENERGYIDLE_CPP_API UTurbineMerger : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTurbineMerger();

private:
	bool bCanMerge;
	UTurbineSpawner* TurbineSpawner;
	UTurbinePlacer* TurbinePlacer;
	UTurbineSelector* TurbineSelector;
	ABaseTurbine* CenterTurbine;
	float CenterTurbineWindMultiplier;
	TArray<ABaseTurbine*>* ClosestTurbines;
	int MergeMovementCompleteCount;

	UFUNCTION()
	void OnTurbineSpawn(ABaseTurbine* Turbine);

	void SetCanMerge();
	void FindClosestObjects(TArray<ABaseTurbine*>* Turbines, bool& bWasSuccessful) const;

	UFUNCTION()
	void OnMergeMovementComplete(ABaseTurbine* Turbine);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void InjectData(UTurbineSpawner* TurbineSpawnerReference, UTurbinePlacer* TurbinePlacerReference, UTurbineSelector*
	                TurbineSelectorReference);

	UFUNCTION(BlueprintCallable)
	void Merge();
};
