// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Actors/Turbine.h"
#include "GameFramework/HUD.h"
#include "GameFramework/Pawn.h"
#include "InputMappingContext.h"
#include "WEI_Pawn.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVoidEvent);

UCLASS()
class WINDENERGYIDLE_CPP_API AWEI_Pawn : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FVoidEvent OnEmptyAreaClicked;

private:
	bool bIsLeftMouseDown;

protected:
	// Expose a mapping context as a property in your header file...
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputActionDot;
	
	// References
	UPROPERTY(BlueprintReadOnly)
	APlayerController* PlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UTurbineSpawner* TurbineSpawner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UTurbineSelector* TurbineSelector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UTurbinePlacer* TurbinePlacer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UTurbineMerger* TurbineMerger;

private:
	UFUNCTION()
	void OnTurbineSpawned(ATurbine* Turbine);
	UFUNCTION()
	void OnTurbineSelected(ATurbine* Turbine);
	UFUNCTION()
	void OnTurbinePlaced(ATurbine* Turbine);
	UFUNCTION()
	void OnTurbinePlacementFailed(ATurbine* Turbine);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	AWEI_Pawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnLeftMouseClickPressed();
	void OnLeftMouseClickRelease();
	UTurbineSelector* GetTurbineSelector();
	UTurbinePlacer* GetTurbinePlacer();
	UTurbineMerger* GetTurbineMerger();
	UTurbineSpawner* GetTurbineSpawner();
};
