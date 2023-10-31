// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Turbines/BaseTurbine.h"
#include "TurbineBlueprintData.generated.h"

/**
 * 
 */
UCLASS()
class WINDENERGYIDLE_CPP_API UTurbineBlueprintData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class ABaseTurbine>> Turbines; 
	
};
