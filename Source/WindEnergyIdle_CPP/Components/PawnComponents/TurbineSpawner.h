// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WindEnergyIdle_CPP/Actors/Turbine.h"
#include "TurbineSpawner.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WINDENERGYIDLE_CPP_API UTurbineSpawner : public UActorComponent
{
	GENERATED_BODY()

#pragma region "Delegates"

public:
	UPROPERTY(BlueprintAssignable)
	FTurbineDelegate OnSpawnStart;

	UPROPERTY(BlueprintAssignable)
	FTurbineDelegate OnSpawnComplete;

	UPROPERTY(BlueprintAssignable)
	FTurbineDelegate OnTurbineAdded;
	
	UPROPERTY(BlueprintAssignable)
	FTurbineDelegate OnTurbineRemoved;
	
#pragma endregion

#pragma region "Properties"

private:
	bool bCanSpawn = true;

	ATurbine* SpawnedTurbine;

	TArray<TArray<ATurbine*>*>* SpawnedTurbinesByLevel = new TArray<TArray<ATurbine*>*>();;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	FRotator SpawnRotation;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	class UTurbineBlueprintData* TurbineBlueprints;
	// TSubclassOf<class ABaseTurbine> TurbineToSpawn;

protected:
	// UPROPERTY(BlueprintReadOnly)
	// TArray<ATurbine*> SpawnedTurbines;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn")
	FVector SpawnLocation;

#pragma endregion

#pragma region "Functions"

private:
	void RemoveToTurbinesByLevels(ATurbine* Turbine) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Sets default values for this component's properties
	UTurbineSpawner();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void SetCanSpawn(bool value);

	UFUNCTION(BlueprintCallable)
	ATurbine* SpawnTurbine(int Level, bool& bWasSuccessful);

	void AddToTurbinesByLevels(ATurbine* Turbine, int Level);
	void RemoveTurbineFromArray(ATurbine* Turbine);
	void DespawnTurbine(ATurbine* Turbine);

	const TArray<TArray<ATurbine*>*>* GetSpawnedTurbinesByLevel() const;

	const UTurbineBlueprintData* GetTurbineBlueprints() const;

#pragma endregion
};
