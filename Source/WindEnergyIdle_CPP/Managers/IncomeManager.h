// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IncomeManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFloatEvent, float, Value);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WINDENERGYIDLE_CPP_API UIncomeManager : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FFloatEvent OnIncomePerSecondChanged;

	UPROPERTY(BlueprintAssignable)
	FFloatEvent OnBoostRatioChanged;
	
private:
	UPROPERTY(EditDefaultsOnly)
	class UUIncomeManagerDataAsset* Data;

	class AWEI_Pawn* Pawn;
	class UResourceManager* ResourceManager;
	class UEnergyManager* EnergyManager;
	class UUpgradeManager* UpgradeManager;

	float CurrentBoost = 1;

protected:
	virtual void BeginPlay() override;

public:	
	UIncomeManager();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void InjectData(UResourceManager* NewResourceManager, UEnergyManager* NewEnergyManager, UUpgradeManager* UpgradeManager, AWEI_Pawn* NewPawn);

private:
	UFUNCTION()
	void OnEmptyAreaClicked();
	void FadeCurrentBoost(float DeltaTime);
	void SetCurrentBoost(float NewBoost);
};
