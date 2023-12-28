// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelLoader.h"
#include "DefaultSaveGame.h"
#include "WEI_GameInstance.h"
#include "DataAssets/LevelListDataAsset.h"

// Sets default values for this component's properties
ULevelLoader::ULevelLoader()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void ULevelLoader::BeginPlay()
{
	Super::BeginPlay();

	InjectData();
}

void ULevelLoader::InjectData()
{
	GameInstance = static_cast<UWEI_GameInstance*>(UGameplayStatics::GetGameInstance(GetWorld()));
	if(GameInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[ULevelLoader] GameInstance is null!"));
		return;
	}
	
	DefaultSaveGame = GameInstance->GetSaveGame();
	if(DefaultSaveGame == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[ULevelLoader] DefaultSaveGame is null!"));
		return;
	}
}

int ULevelLoader::GetLevelIndex(int LevelNumber)
{
	const auto NumberOfLevels = LevelList->Levels.Num();
	UE_LOG(LogTemp, Log, TEXT("[ULevelLoader] GetLevelIndex_Implementation, NumberOfLevels: %d"), NumberOfLevels);
	const auto CurrentIndex = LevelNumber - 1;
	auto Index = CurrentIndex;
	const auto LoopCount = static_cast<float>(CurrentIndex) / NumberOfLevels;
	if(LoopCount >= 1)
	{
		constexpr auto LoopLevelFrom = 1;
		const auto LoopedLevelCount = NumberOfLevels - LoopLevelFrom + 1;
		Index = (CurrentIndex - NumberOfLevels) % LoopedLevelCount;
		Index += LoopLevelFrom - 1;
	}

	return Index;
}

void ULevelLoader::LoadMaxLevel()
{
	if(DefaultSaveGame == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[ULevelLoader] DefaultSaveGame is null!"));
		return;
	}
	
	const auto LevelNumber = DefaultSaveGame->GetMaxLevelNumber();
	LoadLevel(LevelNumber);
}

void ULevelLoader::LoadLastLevel()
{
	if(DefaultSaveGame == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[ULevelLoader] DefaultSaveGame is null!"));
		return;
	}
	
	const auto LevelNumber = DefaultSaveGame->GetLastLevelNumber();
	UE_LOG(LogTemp, Log, TEXT("[ULevelLoader] LevelNumber = %d"), LevelNumber);
	LoadLevel(LevelNumber);
}

void ULevelLoader::LoadPreviousLevel()
{
	if(DefaultSaveGame == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[ULevelLoader] DefaultSaveGame is null!"));
		return;
	}
	
	const auto LevelNumber = DefaultSaveGame->GetLastLevelNumber() - 1;
	LoadLevel(LevelNumber);
}

void ULevelLoader::LoadNextLevel()
{
	if(DefaultSaveGame == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[ULevelLoader] DefaultSaveGame is null!"));
		return;
	}

	const auto LevelNumber = DefaultSaveGame->GetLastLevelNumber() + 1;
	LoadLevel(LevelNumber);
}
