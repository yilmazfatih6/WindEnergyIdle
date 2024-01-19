// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WindEnergyIdle_CPP/Core/WEI_Pawn.h"
#include "Upgrade.generated.h"


class AWEI_Pawn;
class UResourceManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUpgradeLevelIncreaseEvent, int, NewLevel, float, NewPrice);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WINDENERGYIDLE_CPP_API UUpgrade : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FUpgradeLevelIncreaseEvent OnLevelIncrease;

protected:
	UResourceManager* ResourceManager;
	AWEI_Pawn* Pawn;
	AWEI_GM* GM;
	bool CanUse;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UUpgradeDataAsset* Data;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	int Level = 1;

public:
	UUpgrade();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void InjectData(UResourceManager* NewResourceManager, AWEI_Pawn* NewPawn);
	virtual void SetCanUse();
	
	UFUNCTION(BlueprintCallable)
	virtual void Use();

	float GetPrice() const;

	int GetLevel() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	AWEI_Pawn* GetWEIPawn();
};
