// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WindEnergyIdle_CPP/Turbines/BaseTurbine.h"
#include "TurbineSpawner.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WINDENERGYIDLE_CPP_API UTurbineSpawner : public UActorComponent
{
	GENERATED_BODY()

#pragma region "Delegates"

public:
	UPROPERTY(BlueprintAssignable)
	;
	FTurbineDelegate OnSpawnStart;

	UPROPERTY(BlueprintAssignable)
	;
	FTurbineDelegate OnSpawnComplete;

#pragma endregion

#pragma region "Properties"

private:
	bool bCanSpawn = true;

	ABaseTurbine* SpawnedTurbine;

	TArray<TArray<ABaseTurbine*>*>* SpawnedTurbinesByLevel;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	FRotator SpawnRotation;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	class UTurbineBlueprintData* TurbineBlueprints;
	// TSubclassOf<class ABaseTurbine> TurbineToSpawn;

protected:
	UPROPERTY(BlueprintReadOnly)
	TArray<ABaseTurbine*> SpawnedTurbines;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn")
	FVector SpawnLocation;

#pragma endregion

#pragma region "Functions"

private:
	void AddToTurbinesByLevels(ABaseTurbine* Turbine, int Level);
	void RemoveToTurbinesByLevels(ABaseTurbine* Turbine) const;

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
	ABaseTurbine* SpawnTurbine(int Level, bool& bWasSuccessful);

	void RemoveTurbineFromArray(ABaseTurbine* Turbine);
	void DespawnTurbine(ABaseTurbine* Turbine);

	const TArray<TArray<ABaseTurbine*>*>* GetSpawnedTurbinesByLevel() const;

	const UTurbineBlueprintData* GetTurbineBlueprints() const;

#pragma endregion
};
