// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTurbine.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTurbineDelegate, ABaseTurbine*, Turbine);

const int MERGE_TURBINE_AMOUNT = 3;

UCLASS()
class WINDENERGYIDLE_CPP_API ABaseTurbine : public AActor
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintAssignable);
	FTurbineDelegate OnMovementComplete;

private:
	bool bIsInitialPlacement = true;
	bool bIsSelected;
	bool bIsOverlapping;
	
	float BaseEnergyPerSecond = 5;
	float WindMultiplier = 0;
	float PreviousWindMultiplier = 0;

	UPROPERTY(EditAnywhere)
	int32 Level = 1;
	
	UPROPERTY(EditAnywhere)
	float MovementSpeed = 1;

	FVector PlacementLocation;
	FVector MovementLocation;
	bool bMove;

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

	void Move();
	void StartMovement(const FVector& TargetMovementLocation);

	bool IsInitialPlacement() const;

	int32 GetLevel() const;
	float GetWindMultiplier() const;
	FVector GetPlacementLocation() const;
};
