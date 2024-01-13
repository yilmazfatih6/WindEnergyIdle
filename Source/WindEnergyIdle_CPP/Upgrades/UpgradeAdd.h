// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Upgrade.h"
#include "UpgradeAdd.generated.h"

/**
 * 
 */
UCLASS()
class WINDENERGYIDLE_CPP_API UUpgradeAdd : public UUpgrade
{
	GENERATED_BODY()

public:

	virtual void Use() override;
};
