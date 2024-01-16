// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Turbine.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTurbineDelegate, ATurbine*, Turbine);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVoidDelegate);

constexpr int MERGE_TURBINE_AMOUNT = 3;

UCLASS()
class WINDENERGYIDLE_CPP_API ATurbine : public AActor
{
	GENERATED_BODY()

#pragma region Delegates
public:
	UPROPERTY(BlueprintAssignable)
	FTurbineDelegate OnMovementComplete;

#pragma endregion

#pragma region Variables
private:
	UPROPERTY(EditDefaultsOnly)
	class UTurbineDataAsset* Data;
	
	bool bIsInitialPlacement = true;
	bool bIsSelected;
	bool bIsOverlapping;

	UPROPERTY(EditDefaultsOnly)
	int32 Level = 1;

	UPROPERTY(EditAnywhere, Category = "Movement")
	UCurveFloat* CurveFloat;

	FTimeline CurveTimeline;
	FVector MovementStartLocation;
	FVector PlacementLocation;
	FVector MovementLocation;

	bool bMove;

	FRotator DefaultRotationRate;
	float BoostRatio = 0;
	
protected:
	UPROPERTY(Category="References", BlueprintReadOnly)
	class AWEI_GM* GameMode;
	
	UPROPERTY(Category="References", EditDefaultsOnly, BlueprintReadOnly)
	UMaterialInstance* SelectionInvalidMaterial;

	UPROPERTY(Category="References", EditDefaultsOnly, BlueprintReadOnly)
	UMaterialInstance* SelectionValidMaterial;
	
	UPROPERTY(Category="Components", BlueprintReadOnly)
	class UTurbineEnergyController* TurbineEnergyController;

	UPROPERTY(Category="Components", EditDefaultsOnly, BlueprintReadOnly)
	class URotatingMovementComponent* RotatingMovementComponent;

	UPROPERTY(Category="Components", EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* RootSceneComponent;
	
	UPROPERTY(Category="Components", EditDefaultsOnly, BlueprintReadOnly)
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(Category="Components", EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* PropellerRoot;

	UPROPERTY(Category="Components", EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* PlacementStatusMesh;

	UPROPERTY(Category="Components", EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* TurbineBodyMesh;

	UPROPERTY(Category="Components", EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* TurbinePropellerMesh;

	UPROPERTY(BlueprintReadOnly)
	float WindMapValue;
#pragma endregion

#pragma region Functions
private:
	UFUNCTION()
	void OnBoostRatioChanged(float Value);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void BeginOverlap(AActor* OtherActor);
	UFUNCTION(BlueprintCallable)
	void EndOverlap(AActor* OtherActor);

public:
	// Sets default values for this actor's properties
	ATurbine();

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
	int32 GetTurbineLevel() const;
	FVector GetPlacementLocation() const;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	FTransform GetEnergyTextPosition() const;

	UFUNCTION(BlueprintCallable)
	virtual void SetWindMapValue(float Value);

	UFUNCTION(BlueprintCallable)
	void SetPropellerRotationRate();
#pragma endregion
};
