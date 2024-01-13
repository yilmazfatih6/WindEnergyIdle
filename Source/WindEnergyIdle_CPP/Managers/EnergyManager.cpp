// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergyManager.h"

#include "ResourceManager.h"
#include "Kismet/GameplayStatics.h"
#include "WindEnergyIdle_CPP/Core/WEI_GM.h"
#include "WindEnergyIdle_CPP/Enums/GameResourceType.h"

// Sets default values for this component's properties
UEnergyManager::UEnergyManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UEnergyManager::InjectData(UResourceManager* NewResourceManager)
{
	ResourceManager = NewResourceManager;
}

// Called when the game starts
void UEnergyManager::BeginPlay()
{
	Super::BeginPlay();

	// ...

	EnergyPerSecond = 0;
	OnEnergyPerSecondDecrease.Broadcast(EnergyPerSecond, TargetEnergyPerSecond, false);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
	{
		if(ResourceManager)
		{
			// UE_LOG(LogTemp, Log, TEXT("EnergyPerSecond %f"), (EnergyPerSecond));
			// UE_LOG(LogTemp, Log, TEXT("IncomePerEnergy %f"), (IncomePerEnergy));

			const int Amount = EnergyPerSecond * IncomePerEnergy * .33f;
			if(Amount > 0)
			{
				ResourceManager->AddResource(EGameResourceType::Money, Amount);
			}
		}
	}, .33f, true);
}


// Called every frame
void UEnergyManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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
