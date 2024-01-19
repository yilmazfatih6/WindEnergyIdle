// Fill out your copyright notice in the Description page of Project Settings.


#include "Upgrade.h"

#include "WindEnergyIdle_CPP/DataAssets/ResourceDataAsset.h"
#include "WindEnergyIdle_CPP/DataAssets/UpgradeDataAsset.h"
#include "WindEnergyIdle_CPP/Enums/GameResourceType.h"
#include "WindEnergyIdle_CPP/Managers/ResourceManager.h"

// Sets default values for this component's properties
UUpgrade::UUpgrade()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UUpgrade::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UUpgrade::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UUpgrade::InjectData(UResourceManager* NewResourceManager, AWEI_Pawn* NewPawn)
{
	ResourceManager = NewResourceManager;
	Pawn = NewPawn;
}

void UUpgrade::SetCanUse()
{
	if(ResourceManager == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[UUpgrade] SetCanUse(), ResourceManager is null!"));
		return;
	}
	
	const auto Price = GetPrice();
	const auto Money = ResourceManager->GetResource(EGameResourceType::Money)->Amount;
	// UE_LOG(LogTemp, Warning, TEXT("[UUpgrade] SetCanUse(), Price = %f"), Price);
	// UE_LOG(LogTemp, Warning, TEXT("[UUpgrade] SetCanUse(), Money = %f"), Money);
	CanUse = Price <= Money;
	if(!CanUse)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UUpgrade] SetCanUse(), Not enough money!"));
	}
}

void UUpgrade::Use()
{
	if(ResourceManager == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[UUpgrade] SetCanUse(), ResourceManager is null!"));
		return;
	}
	
	SetCanUse();

	if(!CanUse) return;

	const auto Price = GetPrice();
	// UE_LOG(LogTemp, Error, TEXT("[UUpgrade] SetCanUse(), Price = %f"), Price);
	ResourceManager->RemoveResource(EGameResourceType::Money, Price);

	// Increase level.
	Level += 1;
	OnLevelIncrease.Broadcast(Level, GetPrice());
}

float UUpgrade::GetPrice() const
{
	return FMath::FloorToInt(Data->PriceGraph->GetFloatValue(Level));
}

int UUpgrade::GetLevel() const
{
	return Level;
}

AWEI_Pawn* UUpgrade::GetWEIPawn()
{
	return Pawn;
}
