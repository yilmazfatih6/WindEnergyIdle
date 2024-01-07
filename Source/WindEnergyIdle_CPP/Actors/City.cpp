// Fill out your copyright notice in the Description page of Project Settings.


#include "City.h"

#include "WindEnergyIdle_CPP/Core/WEI_GM.h"
#include "WindEnergyIdle_CPP/Actors/Building.h"
#include "WindEnergyIdle_CPP/Managers/EnergyManager.h"
#include "WindEnergyIdle_CPP/Managers/LevelManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACity::ACity()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ACity::BeginPlay()
{
	Super::BeginPlay();
	
	GameMode = static_cast<AWEI_GM*>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->EnergyManager->OnEnergyPerSecondIncrease.AddDynamic(this, &ThisClass::OnEnergyPerSecondIncrease);
	GameMode->EnergyManager->OnEnergyPerSecondDecrease.AddDynamic(this, &ThisClass::OnEnergyPerSecondDecrease);
	
	GetBuildings();
}

void ACity::GetBuildings()
{
	// Get list of buildings inside this City.
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	// UE_LOG(LogTemp, Log, TEXT("[ACity] ACity(), AttachedActors.Num() = %d"), AttachedActors.Num());
	for (const auto AttachedActor : AttachedActors)
	{
		// UE_LOG(LogTemp, Log, TEXT("[ACity] ACity(), AttachedActor->GetName() = %s"), *AttachedActor->GetName());
		if (AttachedActor && AttachedActor->IsA(ABuilding::StaticClass()))
		{
			ABuilding* Building = Cast<ABuilding>(AttachedActor);
			if (Building)
			{
				Building->Initialize();
				LightCount += Building->GetMaterialCount();
				Buildings.Add(Building);
				CompletelyOffBuildings.Add(Building);
			}
		}
	}

	UE_LOG(LogTemp, Log, TEXT("[ACity] ACity(), LightCount = %d"), LightCount);
}

void ACity::OnEnergyPerSecondIncrease(const float CurrentEnergy, const float TargetEnergy)
{
	const auto Ratio = CurrentEnergy / TargetEnergy;
	SetLights(Ratio);
}

void ACity::OnEnergyPerSecondDecrease(const float CurrentEnergy, const float TargetEnergy, bool IsTurbineDespawned)
{
	if(IsTurbineDespawned) return;
	const auto Ratio = CurrentEnergy / TargetEnergy;
	SetLights(Ratio);
}

void ACity::SetLights(float Ratio)
{
	UE_LOG(LogTemp, Log, TEXT("[ACity] OnEnergyPerSecondChange()"));
	UE_LOG(LogTemp, Log, TEXT("[ACity] OnEnergyPerSecondChange(), Ratio = %f"), Ratio);
	OnLightCount = FMath::FloorToInt(LightCount * Ratio);	
	UE_LOG(LogTemp, Log, TEXT("[ACity] OnEnergyPerSecondChange(), OnLightCount = %d"), OnLightCount);
	OnLightCount = FMath::Clamp(OnLightCount, 0, LightCount);	
	UE_LOG(LogTemp, Log, TEXT("[ACity] OnEnergyPerSecondChange(), Clamped OnLightCount = %d"), OnLightCount);
	UE_LOG(LogTemp, Log, TEXT("[ACity] OnEnergyPerSecondChange(), CurrentOnLightCount = %d"), CurrentOnLightCount);

	if(OnLightCount == CurrentOnLightCount) return;
	if(OnLightCount > CurrentOnLightCount)
	{
		for (int i = 0; i < OnLightCount - CurrentOnLightCount; i++)
		{
			TurnOnRandomLight();
		}
	}
	else if (OnLightCount < CurrentOnLightCount)
	{
		for (int i = 0; i < CurrentOnLightCount - OnLightCount ; i++)
		{
			TurnOffRandomLight();
		}
	}
	CurrentOnLightCount = OnLightCount;
}

void ACity::TurnOnRandomLight()
{
	UE_LOG(LogTemp, Log, TEXT("[ACity] TurnOnRandomLight()"));

	/*
	 * Get a reference to building.
	 */
	ABuilding* CurrentBuilding = nullptr;
	if(CompletelyOffBuildings.Num() > 0)
	{
		UE_LOG(LogTemp, Log, TEXT("[ACity] TurnOnRandomLight(), Turn on from CompletelyOffBuildings"));
		const int Index = FMath::RandRange(0, CompletelyOffBuildings.Num() - 1);
		CurrentBuilding = CompletelyOffBuildings[Index];

		CompletelyOffBuildings.Remove(CurrentBuilding);
		SemiOnBuildings.Add(CurrentBuilding);
	}
	else if (SemiOnBuildings.Num() > 0)
	{
		UE_LOG(LogTemp, Log, TEXT("[ACity] TurnOnRandomLight(), Turn on from SemiOnBuildings"));
		const int Index = FMath::RandRange(0, SemiOnBuildings.Num() - 1);
		CurrentBuilding = SemiOnBuildings[Index];
	}

	/*
	 * Return and log error if no building is found!
	 */
	if(CurrentBuilding == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[ACity] TurnRandomLightOn(), CurrentBuilding is nullptr!"));
		return;
	}

	/*
	 * Turn on light in building
	 */
	bool IsCompletelyOn;
	CurrentBuilding->TurnOnRandomLight(IsCompletelyOn);

	/*
	 * Modify list if all lights in the building are completely turned on
	 */
	if(IsCompletelyOn)
	{
		CompletelyOnBuildings.Add(CurrentBuilding);
		SemiOnBuildings.Remove(CurrentBuilding);
	}

	/*
	 * Complete level from here.
	 */
	UE_LOG(LogTemp, Log, TEXT("[ACity] SemiOnBuildings.Num() = %d"), SemiOnBuildings.Num());
	UE_LOG(LogTemp, Log, TEXT("[ACity] CompletelyOffBuildings.Num() = %d"), CompletelyOffBuildings.Num());
	if(SemiOnBuildings.Num() == 0 && CompletelyOffBuildings.Num() == 0)
	{
		UE_LOG(LogTemp, Log, TEXT("[ACity] All lights are turned on!"));
		GameMode->LevelManager->CompleteLevel();
	}
}

void ACity::TurnOffRandomLight()
{
	/*
 * Get a reference to building.
 */
	ABuilding* CurrentBuilding = nullptr;
	if(CompletelyOnBuildings.Num() > 0)
	{
		const int Index = FMath::RandRange(0, CompletelyOnBuildings.Num() - 1);
		CurrentBuilding = CompletelyOnBuildings[Index];

		CompletelyOnBuildings.Remove(CurrentBuilding);
		SemiOnBuildings.Add(CurrentBuilding);
	}
	else if (SemiOnBuildings.Num() > 0)
	{
		const int Index = FMath::RandRange(0, SemiOnBuildings.Num() - 1);
		CurrentBuilding = SemiOnBuildings[Index];
	}

	/*
	 * Return and log error if no building is found!
	 */
	if(CurrentBuilding == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[ACity] TurnRandomLightOn(), CurrentBuilding is nullptr!"));
		return;
	}

	/*
	 * Turn off light in building
	 */
	bool IsCompletelyOff;
	CurrentBuilding->TurnOffRandomLight(IsCompletelyOff);

	/*
	 * Modify list if all lights in the building are completely turned off
	 */
	if(IsCompletelyOff)
	{
		CompletelyOffBuildings.Add(CurrentBuilding);
		SemiOnBuildings.Remove(CurrentBuilding);
	}
}

