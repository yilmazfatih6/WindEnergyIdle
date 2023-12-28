// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LevelLoader.generated.h"

class UDefaultSaveGame;
class UWEI_GameInstance;
class ULevelListDataAsset;

UCLASS(ClassGroup = (Custom), BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class WINDENERGYIDLE_CPP_API ULevelLoader : public UActorComponent
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadOnly)
	UWEI_GameInstance* GameInstance;
	
	UPROPERTY(BlueprintReadOnly)
	UDefaultSaveGame* DefaultSaveGame;

	UPROPERTY(BlueprintReadWrite)
	TSoftObjectPtr<UWorld> CurrentLevel;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ULevelListDataAsset* LevelList;

protected:
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void LoadLevel(int LevelNumber);
	
public:
	
	// Sets default values for this component's properties
	ULevelLoader();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void InjectData();
	
	UFUNCTION(BlueprintCallable)
	int GetLevelIndex(int LevelNumber);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void UnloadLevel();

	UFUNCTION(BlueprintCallable)
	void LoadMaxLevel();
	
	UFUNCTION(BlueprintCallable)
	void LoadLastLevel();
	
	UFUNCTION(BlueprintCallable)
	void LoadPreviousLevel();

	UFUNCTION(BlueprintCallable)
	void LoadNextLevel();
};
