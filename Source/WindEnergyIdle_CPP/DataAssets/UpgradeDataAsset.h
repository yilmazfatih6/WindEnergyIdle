// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UpgradeDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class WINDENERGYIDLE_CPP_API UUpgradeDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	;
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	;
	UTexture* Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	;
	UCurveFloat* PriceGraph;
};
