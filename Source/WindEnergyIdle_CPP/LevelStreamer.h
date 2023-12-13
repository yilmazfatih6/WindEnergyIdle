// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelStreamer.generated.h"

class UDefaultSaveGame;
class UWEI_GameInstance;
class ULevelListDataAsset;

UCLASS()
class WINDENERGYIDLE_CPP_API ALevelStreamer : public AActor
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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	ALevelStreamer();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void InjectData(UWEI_GameInstance* CurrentGameInstance);
	
	UFUNCTION(BlueprintCallable)
	int GetLevelIndex(int LevelNumber);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void UnloadLevel();
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void LoadLevel(int LevelNumber);

	UFUNCTION(BlueprintCallable)
	void LoadMaxLevel();
	
	UFUNCTION(BlueprintCallable)
	void LoadLastLevel();
	
	UFUNCTION(BlueprintCallable)
	void LoadPreviousLevel();

	UFUNCTION(BlueprintCallable)
	void LoadNextLevel();
};
