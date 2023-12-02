// Fill out your copyright notice in the Description page of Project Settings.


#include "TurbineSelector.h"

#include "Kismet/GameplayStatics.h"
#include "WindEnergyIdle_CPP/Turbines/BaseTurbine.h"

// Sets default values for this component's properties
UTurbineSelector::UTurbineSelector()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

// Called when the game starts
void UTurbineSelector::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UTurbineSelector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTurbineSelector::SetSelectedTurbine(ABaseTurbine* Turbine)
{
	SetCanSelect(false);
	SelectedTurbine = Turbine;
	SelectedTurbine->SetSelected();
	
	OnSelect.Broadcast(SelectedTurbine);
	UE_LOG(LogTemp, Log, TEXT("[UTurbineSelector] SetSelectedTurbine, Turbine: %s"), *SelectedTurbine->GetName());
}

void UTurbineSelector::ResetSelectedTurbine()
{
	SetCanSelect(true);
	SelectedTurbine->SetUnselected();
	SelectedTurbine = nullptr;
	OnUnselect.Broadcast();
}

void UTurbineSelector::LineTraceTurbine()
{
	if(!bCanSelect) return;

	// bMoveToPickupLocation = false;

	PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	const FVector TraceEnd = WorldLocation + WorldDirection * TraceDistance;

	QueryParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(Hit, WorldLocation, TraceEnd, TraceChannelPropertyTurbine, QueryParams);
	// DrawDebugLine(GetWorld(), WorldLocation, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);

	// if(!Hit.IsValidBlockingHit()) return;
	if(Hit.GetActor() == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Select turbine trace. Hit actor is null!"));
		return;
	}
	ABaseTurbine * HitTurbine = Cast<ABaseTurbine>(Hit.GetActor());

	if(HitTurbine == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Select turbine trace. Selected turbine is null!"));
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("[WEI_Pawn] SelectTurbine, Turbine: %s"), *HitTurbine->GetName());

	SetSelectedTurbine(HitTurbine);

	// OnTurbinePlacementStart.Broadcast();
}

void UTurbineSelector::SetCanSelect(const bool bValue)
{
	bCanSelect = bValue;
}

ABaseTurbine* UTurbineSelector::GetSelectedTurbine() const
{
	return SelectedTurbine;
}
