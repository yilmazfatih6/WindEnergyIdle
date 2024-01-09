// Fill out your copyright notice in the Description page of Project Settings.


#include "MapLoader.h"

#include "DefaultSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "WindEnergyIdle_CPP/Core/WEI_GI.h"
#include "WindEnergyIdle_CPP/DataAssets/LevelDataAsset.h"
#include "WindEnergyIdle_CPP/DataAssets/LevelListDataAsset.h"

UMapLoader::UMapLoader()
{
}

void UMapLoader::InjectData(UWEI_GI* NewGameInstance, ULevelListDataAsset* NewLevelList, UDefaultSaveGame* NewSaveGameObject)
{
	GameInstance = NewGameInstance;
	LevelList = NewLevelList;
	DefaultSaveGame = NewSaveGameObject;
}

int UMapLoader::GetLevelIndex(const int LevelNumber) const
{
	const auto NumberOfLevels = LevelList->LevelsDataAssets.Num();
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
	UE_LOG(LogTemp, Log, TEXT("[ULevelLoader] GetLevelIndex %d"), Index);
	return Index;
}

ULevelDataAsset* UMapLoader::GetCurrentLevelData() const
{
	auto Index = GetLevelIndex(DefaultSaveGame->Level);
	Index = FMath::Clamp(Index, 0, LevelList->LevelsDataAssets.Num() - 1);
	return LevelList->LevelsDataAssets[Index];
}

void UMapLoader::LoadCurrentLevel() const
{
	LoadLevel(DefaultSaveGame->Level);
}

void UMapLoader::LoadPreviousLevel() const
{
	LoadLevel(DefaultSaveGame->Level - 1);
}

void UMapLoader::LoadNextLevel() const
{
	LoadLevel(DefaultSaveGame->Level + 1);
}

void UMapLoader::LoadLevel(const int LevelNumber) const
{
	DefaultSaveGame->Level = LevelNumber;
	const auto Level = GetCurrentLevelData()->Level;
	UE_LOG(LogTemp, Warning, TEXT("Load level %s"), *Level.GetLongPackageName());
	UGameplayStatics::OpenLevelBySoftObjectPtr(GameInstance->GetWorld(), Level);
	UE_LOG(LogTemp, Warning, TEXT("Load level %s is completed"), *Level.GetLongPackageName());
}
