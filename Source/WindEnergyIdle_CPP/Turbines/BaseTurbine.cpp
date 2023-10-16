// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTurbine.h"

#include "WindEnergyIdle_CPP/WindEnergyIdle_CPPGameModeBase.h"
#include "WindEnergyIdle_CPP/Managers/EnergyManager.h"

// Sets default values
ABaseTurbine::ABaseTurbine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseTurbine::BeginOverlap()
{
	bIsOverlapping = true;

	SelectionMesh->SetMaterial(0, SelectionInvalidMaterial);
}

void ABaseTurbine::EndOverlap()
{
	bIsOverlapping = false;

	SelectionMesh->SetMaterial(0, SelectionValidMaterial);
}

// Called when the game starts or when spawned
void ABaseTurbine::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("[BaseTurbine] BeginPlay"));

	placementLocation = GetActorLocation();

	EndOverlap();
	
	SetUnselected();
}

// Called every frame
void ABaseTurbine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveToPlacementLocation();
}

void ABaseTurbine::SetSelected()
{
	EndOverlap();
	bIsSelected = true;
	SelectionMesh->SetVisibility(true);
}

void ABaseTurbine::SetUnselected()
{
	bIsSelected = false;
	SelectionMesh->SetVisibility(false);
}

void ABaseTurbine::	Place()
{
	bIsInitialPlacement = false;
	
	AWindEnergyIdle_CPPGameModeBase* GameMode = static_cast<AWindEnergyIdle_CPPGameModeBase*>(GetWorld()->GetAuthGameMode());

	windMultiplier = 1;

	float EnergyDifference = (baseEnergyPerSecond * windMultiplier) - (baseEnergyPerSecond * previousWindMultiplier);

	previousWindMultiplier = windMultiplier;
	UE_LOG(LogTemp, Log, TEXT("[BaseTurbine] EnergyDifference = %f"), EnergyDifference);

	if(EnergyDifference > 0)
	{
		GameMode->EnergyManager->IncreaseEnergyPerSecond(EnergyDifference);
		UE_LOG(LogTemp, Log, TEXT("[BaseTurbine] Increase Energy Per Second!"));
	}
	else if(EnergyDifference < 0)
	{
		GameMode->EnergyManager->DecreaseEnergyPerSecond(EnergyDifference);
		UE_LOG(LogTemp, Log, TEXT("[BaseTurbine] Decrease Energy Per Second!"));
	}

	placementLocation = GetActorLocation();
	
}

bool ABaseTurbine::IsOverlapping() const
{
	return bIsOverlapping;
}

void ABaseTurbine::MoveToPlacementLocation()
{
	if(!bMoveToPlacementLocation) return;

	FVector start = GetActorLocation();
	FVector end = placementLocation;
	float difference = FVector::Dist(start, end);
	
	if(difference <= 0.1f)
	{
		UE_LOG(LogTemp, Log, TEXT("[ABaseTurbine] MoveToPlacementLocation, Movement is completed!"));
		bMoveToPlacementLocation = false;
		return;
	}

	SetActorLocation(FMath::Lerp(start, end, GetWorld()->DeltaTimeSeconds * MovementSpeed));
	UE_LOG(LogTemp, Log, TEXT("[ABaseTurbine] MoveToPlacementLocation, SetActorLocation: %s"), *GetName());
}

void ABaseTurbine::StartMovementToPlacementLocation()
{
	bMoveToPlacementLocation = true;
}

bool ABaseTurbine::IsInitialPlacement()
{
	return bIsInitialPlacement;
}
