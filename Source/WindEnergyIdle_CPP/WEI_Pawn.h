// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTurbine.h"
#include "GameFramework/HUD.h"
#include "GameFramework/Pawn.h"
#include "InputMappingContext.h"
#include "WEI_Pawn.generated.h"

UCLASS()
class WINDENERGYIDLE_CPP_API AWEI_Pawn : public APawn
{
	GENERATED_BODY()

private:

	// References
	APlayerController* PlayerController;

	// Flags
	bool bIsLeftMouseDown;
	bool bMoveToPickupLocation;

	// Spawn and placement
	float MovementSpeed = 1;
	FVector PickupLocation;
	FVector PlacementLocation;
	FTransform* SpawnTransform;
	ABaseTurbine* SelectedTurbine;
	ABaseTurbine* PreviouslySelectedTurbine;

	// Tracing
	FCollisionQueryParams QueryParams;
	FHitResult Hit;
	FVector WorldLocation;
	FVector WorldDirection;
	
	// Exposed
	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	FRotator SpawnRotation;
	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TSubclassOf<class ABaseTurbine> TurbineToSpawn;
	UPROPERTY(EditDefaultsOnly, Category="Collision")
	float TraceDistance = 10000000;
	UPROPERTY(EditDefaultsOnly, Category="Collision")
	TEnumAsByte<ECollisionChannel> TraceChannelPropertyGround = ECC_Pawn;
	UPROPERTY(EditDefaultsOnly, Category="Collision")
	TEnumAsByte<ECollisionChannel> TraceChannelPropertyTurbine = ECC_Pawn;

protected:
	// Expose a mapping context as a property in your header file...
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputAction;
	
public:
	// Sets default values for this pawn's properties
	AWEI_Pawn();

private:
	
	void HoverSelectedTurbine();
	void SelectTurbine();
	void PlaceSelectedTurbine();
	void MoveBackToPickupLocation();
	void MoveToPickUpLocation() const;
	
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

	UFUNCTION(BlueprintCallable)
	void SpawnTurbine();
};
