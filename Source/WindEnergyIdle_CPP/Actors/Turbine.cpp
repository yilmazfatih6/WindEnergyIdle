// Fill out your copyright notice in the Description page of Project Settings.

#include "Turbine.h"

#include "WindEnergyIdle_CPP/Components/TurbineComponents/TurbineEnergyController.h"

// Sets default values
ATurbine::ATurbine()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurbineEnergyController = CreateDefaultSubobject<UTurbineEnergyController>(TEXT("Energy Controller"));
}

void ATurbine::BeginOverlap(AActor* OtherActor)
{
	if (OtherActor == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("[ABaseTurbine] BeginOverlap, Other actor is null!"));
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("[ABaseTurbine] BeginOverlap"));

	const auto ThisActor = static_cast<AActor*>(this);
	UE_LOG(LogTemp, Log, TEXT("[ABaseTurbine] BeginOverlap, OtherActor: %s"), *OtherActor->GetName());
	UE_LOG(LogTemp, Log, TEXT("[ABaseTurbine] BeginOverlap, ThisActor: %s"), *ThisActor->GetName());

	if (OtherActor == ThisActor)
	{
		return;
	}
	if (!OtherActor->IsA(StaticClass()))
	{
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("[ABaseTurbine] BeginOverlap, overlapping!"));

	bIsOverlapping = true;

	SelectionMesh->SetMaterial(0, SelectionInvalidMaterial);
}

void ATurbine::EndOverlap(AActor* OtherActor)
{
	if (OtherActor == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("[ABaseTurbine] EndOverlap, Other actor is null!"));
		return;
	}
	if (!OtherActor->IsA(StaticClass()))
	{
		return;
	}
	DisableOverlap();
}

// Called when the game starts or when spawned
void ATurbine::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("[BaseTurbine] BeginPlay"));

	PlacementLocation = GetActorLocation();

	DisableOverlap();
}

// Called every frame
void ATurbine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurveTimeline.TickTimeline(DeltaTime);
}

void ATurbine::SetSelected()
{
	DisableOverlap();
	bIsSelected = true;
	SelectionMesh->SetVisibility(true);
}

void ATurbine::SetUnselected()
{
	bIsSelected = false;
	SelectionMesh->SetVisibility(false);
}

void ATurbine::Place()
{
	bIsInitialPlacement = false;
	TurbineEnergyController->SetEnergy();
	PlacementLocation = GetActorLocation();
}

bool ATurbine::IsOverlapping() const
{
	return bIsOverlapping;
}

void ATurbine::Move(float Value)
{
	// if(!bMove) return;
	const FVector NewLocation = FMath::Lerp(MovementStartLocation, MovementLocation, Value);
	SetActorLocation(NewLocation);
}

void ATurbine::StartMovement(const FVector& TargetMovementLocation)
{
	if (CurveFloat == nullptr)
	{
		return;
	}

	MovementLocation = TargetMovementLocation;
	MovementStartLocation = GetActorLocation();

	FOnTimelineFloat OnTimelineUpdate;
	FOnTimelineEvent OnTimelineFinish;

	OnTimelineUpdate.BindDynamic(this, &ThisClass::Move);
	OnTimelineFinish.BindDynamic(this, &ThisClass::EndMovement);

	CurveTimeline.AddInterpFloat(CurveFloat, OnTimelineUpdate);
	CurveTimeline.SetTimelineFinishedFunc(OnTimelineFinish);
	CurveTimeline.SetLooping(false);
	CurveTimeline.PlayFromStart();
}

void ATurbine::EndMovement()
{
	UE_LOG(LogTemp, Log, TEXT("[ABaseTurbine] EndMovement"));
	OnMovementComplete.Broadcast(this);
}

void ATurbine::DisableOverlap()
{
	bIsOverlapping = false;
	SelectionMesh->SetMaterial(0, SelectionValidMaterial);
}

bool ATurbine::IsInitialPlacement() const
{
	return bIsInitialPlacement;
}

UTurbineEnergyController* ATurbine::GetEnergyController() const
{
	return TurbineEnergyController;
}

int32 ATurbine::GetLevel() const
{
	return Level;
}

FVector ATurbine::GetPlacementLocation() const
{
	return PlacementLocation;
}
