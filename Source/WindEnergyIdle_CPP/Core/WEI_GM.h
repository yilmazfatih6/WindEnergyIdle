// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WEI_GM.generated.h"

/**
 * 
 */
UCLASS()
class WINDENERGYIDLE_CPP_API AWEI_GM : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UEnergyManager* EnergyManager;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UUpgradeManager* UpgradeManager;

	UPROPERTY(BlueprintReadOnly)
	class ULevelManager* LevelManager;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UResourceManager* ResourceManager;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UIncomeManager* IncomeManager;
	
	AWEI_GM();
};
