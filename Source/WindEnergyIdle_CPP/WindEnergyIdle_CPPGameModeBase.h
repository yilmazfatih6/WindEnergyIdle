// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WindEnergyIdle_CPPGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class WINDENERGYIDLE_CPP_API AWindEnergyIdle_CPPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly)
	class UEnergyManager* EnergyManager;

	UPROPERTY(BlueprintReadOnly)
	class UUpgradeManager* UpgradeManager;

	UPROPERTY(BlueprintReadOnly)
	class ULevelManager* LevelManager;

	AWindEnergyIdle_CPPGameModeBase();
};
