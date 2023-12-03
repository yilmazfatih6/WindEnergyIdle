// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "BaseTurbine.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTurbineDelegate, ABaseTurbine*, Turbine);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVoidDelegate);

constexpr int MERGE_TURBINE_AMOUNT = 3;

UCLASS()
class WINDENERGYIDLE_CPP_API ABaseTurbine : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	;
	FTurbineDelegate OnMovementComplete;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UTurbineEnergyController* TurbineEnergyController;

private:
	bool bIsInitialPlacement = true;
	bool bIsSelected;
	bool bIsOverlapping;

	UPROPERTY(EditAnywhere)
	int32 Level = 1;

	UPROPERTY(EditAnywhere, Category = "Movement")
	;
	UCurveFloat* CurveFloat;

	FTimeline CurveTimeline;
	FVector MovementStartLocation;
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
	void BeginOverlap(AActor* OtherActor);
	UFUNCTION(BlueprintCallable)
	void EndOverlap(AActor* OtherActor);

public:
	// Sets default values for this actor's properties
	ABaseTurbine();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSelected();
	void SetUnselected();

	virtual void Place();

	bool IsOverlapping() const;

	void StartMovement(const FVector& TargetMovementLocation);

	UFUNCTION()
	void Move(float Value);

	UFUNCTION()
	void EndMovement();

	void DisableOverlap();

	bool IsInitialPlacement() const;

	UTurbineEnergyController* GetEnergyController() const;
	int32 GetLevel() const;
	FVector GetPlacementLocation() const;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	FTransform GetEnergyTextPosition() const;
};
