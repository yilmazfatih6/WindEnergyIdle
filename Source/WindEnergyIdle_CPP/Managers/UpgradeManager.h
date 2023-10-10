// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WindEnergyIdle_CPP/Upgrades/UpgradeIncome.h"
#include "WindEnergyIdle_CPP/Upgrades/UpgradeMerge.h"
#include "UpgradeManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WINDENERGYIDLE_CPP_API UUpgradeManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUpgradeManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
	UPROPERTY(BlueprintReadOnly)
	class UUpgradeAdd* UpgradeAdd;
	
	UPROPERTY(BlueprintReadOnly)
	class UUpgradeMerge* UpgradeMerge;

	UPROPERTY(BlueprintReadOnly)
	class UUpgradeIncome* UpgradeIncome;
};
