// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ResourceManager.h"
#include "Components/ActorComponent.h"
#include "EnergyManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEnergyIncreaseEvent, float, EnergyPerSecond, float, TargetEnergy);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FEnergyDecreaseEvent, float, EnergyPerSecond, float, TargetEnergy, bool, IsTurbineDespawned);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WINDENERGYIDLE_CPP_API UEnergyManager : public UActorComponent
{
public:
	UPROPERTY(BlueprintAssignable);
	FEnergyIncreaseEvent OnEnergyPerSecondIncrease;
	UPROPERTY(BlueprintAssignable);
	FEnergyDecreaseEvent OnEnergyPerSecondDecrease;

	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEnergyManager();

	void InjectData(UResourceManager* NewResourceManager);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	float IncreaseEnergyPerSecond(float Value);
	UFUNCTION(BlueprintCallable)
	float DecreaseEnergyPerSecond(float Value, const bool IsTurbineDespawned = false);
	UFUNCTION(BlueprintCallable)
	float GetEnergyPerSecond() const;
	UFUNCTION(BlueprintCallable)
	float GetTargetEnergy() const;
	UFUNCTION(BlueprintCallable)
	virtual void SetDependencies(float TargetEnergy);
	
private:
	UResourceManager* ResourceManager;
	float IncomePerEnergy = .1f;
	float EnergyPerSecond;
	float TargetEnergyPerSecond;
};