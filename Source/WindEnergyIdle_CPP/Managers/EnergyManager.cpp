// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergyManager.h"

#include "WindEnergyIdle_CPP/Core/WEI_Pawn.h"
#include "WindEnergyIdle_CPP/DataAssets/EnergyManagerDataAsset.h"
#include "WindEnergyIdle_CPP/Enums/GameResourceType.h"

// Sets default values for this component's properties
UEnergyManager::UEnergyManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UEnergyManager::BeginPlay()
{
	Super::BeginPlay();

	EnergyPerSecond = 0;
	OnEnergyPerSecondDecrease.Broadcast(EnergyPerSecond, TargetEnergyPerSecond, false);
}

// Called every frame
void UEnergyManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

float UEnergyManager::IncreaseEnergyPerSecond(const float Value)
{
	EnergyPerSecond += Value;
	EnergyPerSecond = FMath::Clamp(EnergyPerSecond, 0 , TargetEnergyPerSecond);
	OnEnergyPerSecondIncrease.Broadcast(EnergyPerSecond, TargetEnergyPerSecond);
	// UE_LOG(LogTemp, Log, TEXT("EnergyPerSecond=%f"), EnergyPerSecond);
	return EnergyPerSecond;
}

float UEnergyManager::DecreaseEnergyPerSecond(const float Value, const bool IsTurbineDespawned)
{
	EnergyPerSecond -= Value;
	EnergyPerSecond = FMath::Clamp(EnergyPerSecond, 0 , TargetEnergyPerSecond);
	OnEnergyPerSecondDecrease.Broadcast(EnergyPerSecond, TargetEnergyPerSecond, IsTurbineDespawned);
	// UE_LOG(LogTemp, Log, TEXT("EnergyPerSecond=%f"), EnergyPerSecond);
	return EnergyPerSecond;
}

float UEnergyManager::GetEnergyPerSecond() const
{
	return EnergyPerSecond;
}

float UEnergyManager::GetTargetEnergy() const
{
	return TargetEnergyPerSecond;
}

void UEnergyManager::SetDependencies(const float TargetEnergy)
{
	TargetEnergyPerSecond = TargetEnergy;
}
