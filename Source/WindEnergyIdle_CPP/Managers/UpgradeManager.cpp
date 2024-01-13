// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeManager.h"

#include "Kismet/GameplayStatics.h"
#include "WindEnergyIdle_CPP/Upgrades/UpgradeAdd.h"

// Sets default values for this component's properties
UUpgradeManager::UUpgradeManager()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	UpgradeAdd = CreateDefaultSubobject<UUpgradeAdd>(TEXT("Upgrade Add"));
	UpgradeMerge = CreateDefaultSubobject<UUpgradeMerge>(TEXT("Upgrade Merge"));
	UpgradeIncome = CreateDefaultSubobject<UUpgradeIncome>(TEXT("Upgrade Income"));
}


// Called when the game starts
void UUpgradeManager::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UUpgradeManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UUpgradeManager::InjectData(UResourceManager* NewResourceManager)
{
	ResourceManager = NewResourceManager;

	const auto Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if(Pawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[UUpgradeManager] BeginPlay(), Pawn is null!"));
		return;
	}

	const auto WEI_Pawn = Cast<AWEI_Pawn>(Pawn);
	if(WEI_Pawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[UUpgradeManager] BeginPlay(), WEI_Pawn is null!"));
		return;
	}
	
	UpgradeAdd->InjectData(ResourceManager, WEI_Pawn);
	UpgradeMerge->InjectData(ResourceManager, WEI_Pawn);
	UpgradeIncome->InjectData(ResourceManager, WEI_Pawn);
}
