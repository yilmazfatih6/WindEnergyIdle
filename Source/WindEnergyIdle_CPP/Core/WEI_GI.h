// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "WEI_GI.generated.h"

/**
 * 
 */
UCLASS()
class WINDENERGYIDLE_CPP_API UWEI_GI : public UGameInstance
{
	GENERATED_BODY()

private:
	class UDefaultSaveGame* DefaultSaveGame;
	const FString& SaveGameSlotName = "Save Game";
	const int UserIndex = 0;
	
public:
	
	UFUNCTION(BlueprintCallable)
	UDefaultSaveGame* GetSaveGame();
	void Save();
	void Load();
	void OnSaveCompleted(const FString& UsedSlotName, const int32 UsedUserIndex, bool bWasSuccessful);
};
