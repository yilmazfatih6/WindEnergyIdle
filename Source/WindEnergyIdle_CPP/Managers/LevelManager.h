// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LevelManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLevelCompleteEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WINDENERGYIDLE_CPP_API ULevelManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FLevelCompleteEvent OnLevelComplete;

public:	
	// Sets default values for this component's properties
	ULevelManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void StartLevel();
	void CompleteLevel();
	void FailLevel();
};
