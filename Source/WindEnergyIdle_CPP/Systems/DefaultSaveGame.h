// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DefaultSaveGame.generated.h"

class UResourceDataAsset;
/**
 * 
 */
UCLASS()
class WINDENERGYIDLE_CPP_API UDefaultSaveGame : public USaveGame
{
	GENERATED_BODY()

private:
	int MaxLevelNumber = 1;
	int LastLevelNumber = 1;
	TArray<UResourceDataAsset*> Resources;
	
public:

	UFUNCTION(BlueprintCallable)
	int GetMaxLevelNumber() const;

	UFUNCTION(BlueprintCallable)
	int SetMaxLevelNumber(int Value);

	UFUNCTION(BlueprintCallable)
	int GetLastLevelNumber() const;

	UFUNCTION(BlueprintCallable)
	int SetLastLevelNumber(int Value);
};
