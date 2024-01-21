// Fill out your copyright notice in the Description page of Project Settings.


#include "TurbinePlacer.h"

#include "Kismet/GameplayStatics.h"
#include "WindEnergyIdle_CPP/Actors/Ground.h"
#include "WindEnergyIdle_CPP/Actors/Turbine.h"

class ATurbine;
// Sets default values for this component's properties
UTurbinePlacer::UTurbinePlacer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

// Called when the game starts
void UTurbinePlacer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UTurbinePlacer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	HoverSelectedTurbine();
}

void UTurbinePlacer::HoverSelectedTurbine()
{
	if (!bHover)
	{
		return;
	}

	if (!TargetTurbine)
	{
		return;
	}

	PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	const FVector TraceEnd = WorldLocation + WorldDirection * TraceDistance;

	QueryParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(Hit, WorldLocation, TraceEnd, TraceChannelPropertyGround, QueryParams);

	const AGround* Ground = static_cast<AGround*>(Hit.GetActor());

	if (Ground == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Ground is null!"));
		return;
	}

	// UE_LOG(LogTemp, Log, TEXT("Hit %s"), *Hit.GetActor()->GetName());

	if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
	{
		TargetTurbine->SetActorLocation(Hit.ImpactPoint);
		OnPlacementChange.Broadcast(TargetTurbine);
	}
}

void UTurbinePlacer::SetTargetTurbine(ATurbine* Turbine)
{
	TargetTurbine = Turbine;
	OnPlacementStart.Broadcast(TargetTurbine);
}

void UTurbinePlacer::SetHover(bool bValue)
{
	bHover = bValue && TargetTurbine != nullptr;
}

bool UTurbinePlacer::IsPlacing() const
{
	return TargetTurbine != nullptr && bHover;
}

FVector UTurbinePlacer::GetWorldLocation() const
{
	return WorldLocation;
}

FVector UTurbinePlacer::GetWorldDirection() const
{
	return WorldDirection;
}

void UTurbinePlacer::Place()
{
	if (!TargetTurbine)
	{
		return;
	}

	if (TargetTurbine->IsOverlapping())
	{
		TargetTurbine->StartMovement(TargetTurbine->GetPlacementLocation());
		OnPlacementFail.Broadcast(TargetTurbine);
		UE_LOG(LogTemp, Log, TEXT("[UTurbinePlacer] Place, Placement failed due to overlap! Turbine: %s"),
		       *TargetTurbine->GetName());
	}
	else
	{
		TargetTurbine->Place();
		OnPlacementSucceed.Broadcast(TargetTurbine);
		UE_LOG(LogTemp, Log, TEXT("[UTurbinePlacer] Place, Turbine: %s"), *TargetTurbine->GetName());
	}

	if (!TargetTurbine->IsInitialPlacement())
	{
		TargetTurbine = nullptr;
	}
	// UE_LOG(LogTemp, Log, TEXT("[WEI_Pawn] PlaceSelectedTurbine, Turbine: %s"), *PreviouslySelectedTurbine->GetName());
}
