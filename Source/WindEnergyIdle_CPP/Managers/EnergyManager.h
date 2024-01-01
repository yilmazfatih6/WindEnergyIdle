// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnergyManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEnergyEvent, float, EnergyPerSecond, float, TargetEnergy);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WINDENERGYIDLE_CPP_API UEnergyManager : public UActorComponent
{
public:
	UPROPERTY(BlueprintAssignable);
	FEnergyEvent OnEnergyPerSecondIncrease;
	UPROPERTY(BlueprintAssignable);
	FEnergyEvent OnEnergyPerSecondDecrease;

	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEnergyManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	float IncreaseEnergyPerSecond(float Value);
	UFUNCTION(BlueprintCallable)
	float DecreaseEnergyPerSecond(float Value);
	UFUNCTION(BlueprintCallable)
	float GetEnergyPerSecond() const;
	UFUNCTION(BlueprintCallable)
	float GetTargetEnergy() const;
	UFUNCTION(BlueprintCallable)
	virtual void SetDependencies(float TargetEnergy);
	
private:
	float EnergyPerSecond;
	float TargetEnergyPerSecond;
};