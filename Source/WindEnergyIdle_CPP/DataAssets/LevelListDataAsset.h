// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelListDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class WINDENERGYIDLE_CPP_API ULevelListDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSoftObjectPtr<UWorld>> Levels;
};
