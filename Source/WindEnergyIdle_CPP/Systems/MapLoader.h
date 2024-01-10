// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapLoader.generated.h"

class ULevelDataAsset;
class UDefaultSaveGame;
class ULevelListDataAsset;
class UWEI_GI;

/**
 * 
 */
UCLASS(BlueprintType)
class WINDENERGYIDLE_CPP_API UMapLoader : public UObject
{
	GENERATED_BODY()

private:
	UWEI_GI* GameInstance;
	ULevelListDataAsset* LevelList;
	UDefaultSaveGame* DefaultSaveGame;
	
public:
	UMapLoader();
	void InjectData(UWEI_GI* NewGameInstance, ULevelListDataAsset* NewLevelList, UDefaultSaveGame* NewSaveGameObject);

	UFUNCTION(BlueprintCallable)
	void LoadCurrentLevel() const;
	UFUNCTION(BlueprintCallable)
	void LoadPreviousLevel() const;
	UFUNCTION(BlueprintCallable)
	void LoadNextLevel() const;

	int GetLevelIndex(int LevelNumber) const;
	UFUNCTION(BlueprintCallable)
	ULevelDataAsset* GetCurrentLevelData() const;
	void LoadLevel(int LevelNumber) const;
	UFUNCTION(BlueprintCallable)
	int GetLevelNumber();
};
