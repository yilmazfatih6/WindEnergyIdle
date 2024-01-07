// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ResourceDataAsset.generated.h"

enum class EResourceType : uint8;
/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WINDENERGYIDLE_CPP_API UResourceDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* Image;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EResourceType Type;

	UPROPERTY(EditDefaultsOnly)
	int DefaultAmount;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Amount;
};
