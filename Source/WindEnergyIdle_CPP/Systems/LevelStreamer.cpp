// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelStreamer.h"

#include "DefaultSaveGame.h"
#include "WindEnergyIdle_CPP/Core/WEI_GI.h"
#include "WindEnergyIdle_CPP/DataAssets/LevelListDataAsset.h"

ALevelStreamer::ALevelStreamer()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALevelStreamer::InjectData(UWEI_GI* CurrentGameInstance)
{
	GameInstance = CurrentGameInstance;
	DefaultSaveGame = GameInstance->GetSaveGame();
}


// Called when the game starts or when spawned
void ALevelStreamer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALevelStreamer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

int ALevelStreamer::GetLevelIndex(int LevelNumber)
{
	const auto NumberOfLevels = LevelList->LevelsDataAssets.Num();
	UE_LOG(LogTemp, Log, TEXT("[ALevelStreamer] GetLevelIndex_Implementation, NumberOfLevels: %d"), NumberOfLevels);
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

void ALevelStreamer::LoadMaxLevel()
{
	const auto LevelNumber = DefaultSaveGame->GetMaxLevelNumber();
	LoadLevel(LevelNumber);
}

void ALevelStreamer::LoadLastLevel()
{
	const auto LevelNumber = DefaultSaveGame->GetLastLevelNumber();
	LoadLevel(LevelNumber);
}

void ALevelStreamer::LoadPreviousLevel()
{
	const auto LevelNumber = DefaultSaveGame->GetLastLevelNumber() - 1;
	LoadLevel(LevelNumber);
}

void ALevelStreamer::LoadNextLevel()
{
	const auto LevelNumber = DefaultSaveGame->GetLastLevelNumber() + 1;
	LoadLevel(LevelNumber);
}