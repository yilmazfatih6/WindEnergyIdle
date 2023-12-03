// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurbineSpawner.h"
#include "Components/ActorComponent.h"
#include "TurbinePlacer.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WINDENERGYIDLE_CPP_API UTurbinePlacer : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	;
	FTurbineDelegate OnPlacementStart;

	UPROPERTY(BlueprintAssignable)
	;
	FTurbineDelegate OnPlacementChange;

	UPROPERTY(BlueprintAssignable)
	;
	FTurbineDelegate OnPlacementSucceed;

	UPROPERTY(BlueprintAssignable)
	;
	FTurbineDelegate OnPlacementFail;

#pragma endregion

private:
	APlayerController* PlayerController;

	bool bHover;

	class ABaseTurbine* TargetTurbine;

	// Tracing
	FCollisionQueryParams QueryParams;
	FHitResult Hit;
	FVector WorldLocation;
	FVector WorldDirection;

	UPROPERTY(EditDefaultsOnly, Category="Collision")
	float TraceDistance = 10000000;

	UPROPERTY(EditDefaultsOnly, Category="Collision")
	TEnumAsByte<ECollisionChannel> TraceChannelPropertyGround = ECC_Pawn;

	UPROPERTY(EditAnywhere)
	UTexture2D* MyTexture2D;

public:
	// Sets default values for this component's properties
	UTurbinePlacer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void HoverSelectedTurbine();
	void Place();
	void SetTargetTurbine(ABaseTurbine* Turbine);
	void SetHover(bool bValue);

	UFUNCTION(BlueprintCallable)
	bool IsPlacing() const;
};
