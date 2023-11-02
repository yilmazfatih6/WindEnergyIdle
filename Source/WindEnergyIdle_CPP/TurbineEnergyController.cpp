// Fill out your copyright notice in the Description page of Project Settings.


#include "TurbineEnergyController.h"
#include "WindEnergyIdle_CPP/WindEnergyIdle_CPPGameModeBase.h"
#include "WindEnergyIdle_CPP/Managers/EnergyManager.h"

// Sets default values for this component's properties
UTurbineEnergyController::UTurbineEnergyController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UTurbineEnergyController::BeginPlay()
{
	Super::BeginPlay();

	// ...
	GameMode = static_cast<AWindEnergyIdle_CPPGameModeBase*>(GetWorld()->GetAuthGameMode());
}


// Called every frame
void UTurbineEnergyController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UTurbineEnergyController::GetWindMultiplier() const
{
	return WindMultiplier;
}

void UTurbineEnergyController::SetEnergy()
{
	WindMultiplier = 1;

	const float EnergyDifference = (BaseEnergyPerSecond * WindMultiplier) - (BaseEnergyPerSecond * PreviousWindMultiplier);

	PreviousWindMultiplier = WindMultiplier;
	UE_LOG(LogTemp, Log, TEXT("[BaseTurbine] EnergyDifference = %f"), EnergyDifference);

	if(EnergyDifference > 0)
	{
		GameMode->EnergyManager->IncreaseEnergyPerSecond(EnergyDifference);
		UE_LOG(LogTemp, Log, TEXT("[BaseTurbine] Increase Energy Per Second!"));
	}
	else if(EnergyDifference < 0)
	{
		GameMode->EnergyManager->DecreaseEnergyPerSecond(EnergyDifference);
		UE_LOG(LogTemp, Log, TEXT("[BaseTurbine] Decrease Energy Per Second!"));
	}
}

void UTurbineEnergyController::ResetEnergy() const
{
	GameMode->EnergyManager->DecreaseEnergyPerSecond(BaseEnergyPerSecond * WindMultiplier);
}
