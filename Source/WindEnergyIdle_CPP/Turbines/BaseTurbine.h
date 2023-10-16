// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTurbine.generated.h"

UCLASS()
class WINDENERGYIDLE_CPP_API ABaseTurbine : public AActor
{
	GENERATED_BODY()

private:
	bool bIsInitialPlacement = true;
	bool bIsSelected;
	bool bIsOverlapping;
	float baseEnergyPerSecond = 5;
	float windMultiplier = 0;
	float previousWindMultiplier = 0;

	UPROPERTY(EditAnywhere)
	float MovementSpeed = 1;

	FVector placementLocation;
	bool bMoveToPlacementLocation;

protected:
	UPROPERTY(Category="References", BlueprintReadWrite)
	UStaticMeshComponent* SelectionMesh;

	UPROPERTY(Category="References", EditDefaultsOnly, BlueprintReadOnly)
	UMaterialInstance* SelectionInvalidMaterial;

	UPROPERTY(Category="References", EditDefaultsOnly, BlueprintReadOnly)
	UMaterialInstance* SelectionValidMaterial;

private:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void BeginOverlap();
	UFUNCTION(BlueprintCallable)
	void EndOverlap();

public:
	// Sets default values for this actor's properties
	ABaseTurbine();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSelected();
	void SetUnselected();

	virtual void Place();
	
	bool IsOverlapping() const;

	void MoveToPlacementLocation();
	void StartMovementToPlacementLocation();

	bool IsInitialPlacement();
};
