// Fill out your copyright notice in the Description page of Project Settings.


#include "TurbinePlacer.h"

#include "Kismet/GameplayStatics.h"
#include "WindEnergyIdle_CPP/Turbines/BaseTurbine.h"

class ABaseTurbine;
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

	// ...
	
}

// Called every frame
void UTurbinePlacer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
		
	HoverSelectedTurbine();
}

void UTurbinePlacer::HoverSelectedTurbine()
{
	if(!bHover) return;

	if(!TargetTurbine) return;

	PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	const FVector TraceEnd = WorldLocation + WorldDirection * TraceDistance;

	QueryParams.AddIgnoredActor(GetOwner());
	
	GetWorld()->LineTraceSingleByChannel(Hit, WorldLocation, TraceEnd, TraceChannelPropertyGround, QueryParams);
	// DrawDebugLine(GetWorld(), WorldLocation, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);

	if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
	{
		// UE_LOG(LogTemp, Log, TEXT("Trace hit actor: %s"), *Hit.GetActor()->GetName());
		TargetTurbine->SetActorLocation(Hit.ImpactPoint);
	}
	else
	{
		// UE_LOG(LogTemp, Log, TEXT("No Actors were hit"));
	}

	// UE_LOG(LogTemp, Log, TEXT("[WEI_Pawn] HoverSelectedTurbine, Turbine: %s"), *SelectedTurbine->GetName());
}

void UTurbinePlacer::MoveBackToPickupLocation()
{
	// UE_LOG(LogTemp, Log, TEXT("[WEI_Pawn] MoveBackToPickupLocation, bMoveToPickupLocation: %s"), bMoveToPickupLocation ? TEXT("True") : TEXT("False"));
	
	// if(!bMoveToPickupLocation) return;

	// if(!PreviouslySelectedTurbine) return;

	// SelectedTurbine->SetActorLocation()
	// UE_LOG(LogTemp, Log, TEXT("[WEI_Pawn] MoveBackToPickupLocation, Turbine: %s"), *PreviouslySelectedTurbine->GetName());

	// // Create a timer
	// FTimerHandle TimerHandle;
	//
	// // Create a delegate that will call the FInterpTo function
	// const FTimerDelegate Delegate = FTimerDelegate::CreateUObject(TargetTurbine, &ABaseTurbine::Move);
	//
	// // Set the timer to call the delegate at a specified interval
	// GetOwner()->GetWorldTimerManager().SetTimer(TimerHandle, Delegate, 0.1f, true);

	// OnTurbinePlacementCanceled.Broadcast();
}

void UTurbinePlacer::SetTargetTurbine(ABaseTurbine* Turbine)
{
	TargetTurbine = Turbine;
}

void UTurbinePlacer::SetHover(bool value)
{
	bHover = value && TargetTurbine != nullptr;
}

void UTurbinePlacer::Place()
{
	if(!TargetTurbine) return;

	if(TargetTurbine->IsOverlapping())
	{
		TargetTurbine->StartMovement(TargetTurbine->GetPlacementLocation());
		OnPlacementFail.Broadcast(TargetTurbine);
		UE_LOG(LogTemp, Log, TEXT("[UTurbinePlacer] Place, Placement failed due to overlap! Turbine: %s"), *TargetTurbine->GetName());
	}
	else
	{
		TargetTurbine->Place();
		OnPlace.Broadcast(TargetTurbine);
		UE_LOG(LogTemp, Log, TEXT("[UTurbinePlacer] Place, Turbine: %s"), *TargetTurbine->GetName());
	}

	if(!TargetTurbine->IsInitialPlacement())
		TargetTurbine = nullptr;
	// UE_LOG(LogTemp, Log, TEXT("[WEI_Pawn] PlaceSelectedTurbine, Turbine: %s"), *PreviouslySelectedTurbine->GetName());
}
