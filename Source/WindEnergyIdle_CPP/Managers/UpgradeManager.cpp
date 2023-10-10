// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeManager.h"

#include "WindEnergyIdle_CPP/Upgrades/UpgradeAdd.h"

// Sets default values for this component's properties
UUpgradeManager::UUpgradeManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	UpgradeAdd = CreateDefaultSubobject<UUpgradeAdd>(TEXT("Upgrade Add"));
	UpgradeMerge = CreateDefaultSubobject<UUpgradeMerge>(TEXT("Upgrade Merge"));
	UpgradeIncome = CreateDefaultSubobject<UUpgradeIncome>(TEXT("Upgrade Income"));
}


// Called when the game starts
void UUpgradeManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UUpgradeManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

