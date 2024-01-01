// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building.generated.h"

UCLASS()
class WINDENERGYIDLE_CPP_API ABuilding : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* LightOffMaterial;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* LightOnMaterial;
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BuildingMeshComponent;

	TArray<UMaterialInterface*> Materials;
	
	UPROPERTY(VisibleAnywhere)
	int MaterialCount;

	TArray<int> OffLightIndices;
	TArray<int> OnLightIndices;
	
public:
	// Sets default values for this actor's properties
	ABuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Initialize();
	int GetMaterialCount() const;

	void TurnOffLights();
	void TurnOnRandomLight(bool& IsCompletelyOn);
	void TurnOffRandomLight(bool& IsCompletelyOff);
};
