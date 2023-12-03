// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurbineSpawner.h"
#include "Components/ActorComponent.h"
#include "TurbineSelector.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WINDENERGYIDLE_CPP_API UTurbineSelector : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	;
	FTurbineDelegate OnSelect;

	UPROPERTY(BlueprintAssignable)
	;
	FVoidDelegate OnUnselect;

private:
	APlayerController* PlayerController;

	bool bCanSelect = true;

	// Turbine references
	ABaseTurbine* SelectedTurbine;
	ABaseTurbine* PreviouslySelectedTurbine;

	FCollisionQueryParams QueryParams;
	FHitResult Hit;
	FVector WorldLocation;
	FVector WorldDirection;

	UPROPERTY(EditDefaultsOnly, Category="Collision")
	float TraceDistance = 10000000;

	UPROPERTY(EditDefaultsOnly, Category="Collision")
	TEnumAsByte<ECollisionChannel> TraceChannelPropertyTurbine = ECC_Pawn;

public:
	// Sets default values for this component's properties
	UTurbineSelector();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void SetSelectedTurbine(ABaseTurbine* Turbine);
	void ResetSelectedTurbine();
	void LineTraceTurbine();
	void SetCanSelect(bool bValue);

	UFUNCTION(BlueprintCallable)
	ABaseTurbine* GetSelectedTurbine() const;
};
