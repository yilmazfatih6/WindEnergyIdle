// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Upgrade.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WINDENERGYIDLE_CPP_API UUpgrade : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UUpgrade();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	int Level = 1;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Use();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UUpgradeDataAsset* Data;
};
