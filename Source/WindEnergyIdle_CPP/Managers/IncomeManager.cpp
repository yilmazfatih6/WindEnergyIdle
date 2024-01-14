// Fill out your copyright notice in the Description page of Project Settings.


#include "IncomeManager.h"

#include "EnergyManager.h"
#include "ResourceManager.h"
#include "WindEnergyIdle_CPP/Core/WEI_Pawn.h"
#include "WindEnergyIdle_CPP/DataAssets/UIncomeManagerDataAsset.h"

UIncomeManager::UIncomeManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UIncomeManager::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
	{
		if(ResourceManager)
		{
			if(Data == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("[UIncomeManager] Data is null!"));
				return;
			}
			
			const auto IncomePerSecond = EnergyManager->GetEnergyPerSecond() * Data->GetIncomePerEnergy() * CurrentBoost;
			OnIncomePerSecondChanged.Broadcast(IncomePerSecond);
			
			const int Amount = IncomePerSecond * Data->GetIncomeUpdateInterval();
			if(Amount > 0)
			{
				ResourceManager->AddResource(EGameResourceType::Money, Amount);
			}
		}
	}, Data->GetIncomeUpdateInterval(), true);
}

void UIncomeManager::InjectData(UResourceManager* NewResourceManager, UEnergyManager* NewEnergyManager, AWEI_Pawn* NewPawn)
{
	EnergyManager = NewEnergyManager;
	ResourceManager = NewResourceManager;
	Pawn = NewPawn;
	Pawn->OnEmptyAreaClicked.AddDynamic(this, &ThisClass::OnEmptyAreaClicked);
}

void UIncomeManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FadeCurrentBoost(DeltaTime);
}

void UIncomeManager::OnEmptyAreaClicked()
{
	if(Data == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[UIncomeManager] Data is null!"));
		return;
	}

	auto NewBoost = CurrentBoost + Data->GetBoostStep();
	NewBoost = FMath::Clamp(NewBoost, 1 , Data->GetMaxBoost());
	CurrentBoost = NewBoost;
	UE_LOG(LogTemp, Error, TEXT("[UIncomeManager] OnEmptyAreaClicked, CurrentBoost = %f"), CurrentBoost);
}

void UIncomeManager::FadeCurrentBoost(float DeltaTime)
{
	if(Data == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[UIncomeManager] Data is null!"));
		return;
	}
	
	auto NewBoost = CurrentBoost - DeltaTime * Data->GetBoostFadeDuration() * Data->GetMaxBoost();
	NewBoost = FMath::Clamp(NewBoost, 1 , NewBoost);
	CurrentBoost = NewBoost;
	UE_LOG(LogTemp, Error, TEXT("[UIncomeManager] FadeCurrentBoost, CurrentBoost = %f"), CurrentBoost);
}
