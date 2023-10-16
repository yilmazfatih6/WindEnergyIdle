// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Turbines/BaseTurbine.h"
#include "TurbineSpawner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTurbineDelegate, ABaseTurbine*, Turbine);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpawnStartDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WINDENERGYIDLE_CPP_API UTurbineSpawner : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable);
	FTurbineDelegate OnSpawn;
	
	UPROPERTY(BlueprintAssignable);
	FOnSpawnStartDelegate OnSpawnStart;

private:
	bool bCanSpawn = true;

	ABaseTurbine* spawnedTurbine;
	
	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	FRotator SpawnRotation;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TSubclassOf<class ABaseTurbine> TurbineToSpawn;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn")
	FVector SpawnLocation;
	
public:	
	// Sets default values for this component's properties
	UTurbineSpawner();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetCanSpawn(bool value);

	UFUNCTION(BlueprintCallable)
	void SpawnTurbine(bool &bWasSuccessful);
};
