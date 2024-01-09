// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "WEI_GI.generated.h"

class UMapLoader;
class UDefaultSaveGame;
class ULevelListDataAsset;
/**
 * 
 */
UCLASS()
class WINDENERGYIDLE_CPP_API UWEI_GI : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ULevelListDataAsset* LevelList;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMapLoader* CurrentMapLoader;
	
	UWEI_GI();

	virtual void Init() override;

	UPROPERTY(BlueprintReadOnly)
	FString SaveGameSlotName;
	
	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	UDefaultSaveGame* SaveGameObject;

	UFUNCTION(BlueprintCallable, Category = "Game Manager")
	void LoadGame();

	UFUNCTION(BlueprintCallable, Category = "Game Manager")
	void SaveGame();

private:
	void LogIfGameWasSavedOrNot(const bool IsSaved);
	
};
