// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Ground.generated.h"

class ABaseTurbine;

UCLASS()
class WINDENERGYIDLE_CPP_API AGround : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Movement");
	UCurveFloat* CurveFloat;
	
	FTimeline CurveTimeline;
	FOnTimelineFloat OnTimelineUpdate;
	FOnTimelineEvent OnTimelineFinish;

	void EnableWindMap();
	void DisableWindMap();

	UFUNCTION()
	void OnTimelineUpdated(float Value);

	UFUNCTION()
	void OnTimelineFinished();
	
public:	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UMaterialInstanceDynamic* MaterialInstanceDynamic;

private:
	UFUNCTION()
	void OnTurbineSelected(ABaseTurbine* Turbine);

	UFUNCTION()
	void OnTurbinePlaced(ABaseTurbine* Turbine);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	AGround();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float GetWindMapValue(FHitResult HitResult);
};
