// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnergyManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnergyEvent, float, EnergyPerSecond);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WINDENERGYIDLE_CPP_API UEnergyManager : public UActorComponent
{
	UPROPERTY(BlueprintAssignable);
	FEnergyEvent OnEnergyChanged;
	
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnergyManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	float IncreaseEnergyPerSecond(float Value);
	float DecreaseEnergyPerSecond(float Value);
	float GetEnergyPerSecond() const;
	
private:
	float EnergyPerSecond;
};
