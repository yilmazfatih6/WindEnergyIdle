// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "City.generated.h"

class ABuilding;

UCLASS()
class WINDENERGYIDLE_CPP_API ACity : public AActor
{
	GENERATED_BODY()
	
private:
	int LightCount;
	int OnLightCount;
	int CurrentOnLightCount;

	UPROPERTY(VisibleAnywhere)
	TArray<ABuilding*> Buildings;
	TArray<ABuilding*> CompletelyOffBuildings;
	TArray<ABuilding*> CompletelyOnBuildings;
	TArray<ABuilding*> SemiOnBuildings;

private:
	UFUNCTION(BlueprintCallable)
	void GetBuildings();

	UFUNCTION()
	void OnEnergyPerSecondChange(float CurrentEnergy, float TargetEnergy);

	void TurnOnRandomLight();
	void TurnOffRandomLight();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	ACity();
};
