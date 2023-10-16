// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Turbines/BaseTurbine.h"
#include "GameFramework/HUD.h"
#include "GameFramework/Pawn.h"
#include "InputMappingContext.h"
#include "WEI_Pawn.generated.h"


UCLASS()
class WINDENERGYIDLE_CPP_API AWEI_Pawn : public APawn
{
	GENERATED_BODY()

protected:
	// References
	UPROPERTY(BlueprintReadOnly)
	APlayerController* PlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UTurbineSpawner* TurbineSpawner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UTurbineSelector* TurbineSelector;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UTurbinePlacer* TurbinePlacer;

private:
	bool bIsLeftMouseDown;

protected:
	// Expose a mapping context as a property in your header file...
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputAction;

public:

	
public:
	// Sets default values for this pawn's properties
	AWEI_Pawn();

private:

	UFUNCTION()
	void OnTurbineSpawned(ABaseTurbine* Turbine);
	UFUNCTION()
	void OnTurbineSelected(ABaseTurbine* Turbine);
	UFUNCTION()
	void OnTurbinePlaced(ABaseTurbine* Turbine);
	UFUNCTION()
	void OnTurbinePlacementFailed(ABaseTurbine* Turbine);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnLeftMouseClickPressed();
	void OnLeftMouseClickRelease();

	
};
