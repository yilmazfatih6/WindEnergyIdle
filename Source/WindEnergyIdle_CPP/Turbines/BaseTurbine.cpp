// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseTurbine.h"

#include "WindEnergyIdle_CPP/TurbineEnergyController.h"

// Sets default values
ABaseTurbine::ABaseTurbine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurbineEnergyController = CreateDefaultSubobject<UTurbineEnergyController>(TEXT("Energy Controller"));
}

void ABaseTurbine::BeginOverlap(AActor* OtherActor)
{
	if(OtherActor == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("[ABaseTurbine] BeginOverlap, Other actor is null!"));
		return;
	}
	
	UE_LOG(LogTemp, Log, TEXT("[ABaseTurbine] BeginOverlap"));

	const auto ThisActor = static_cast<AActor*>(this);
	UE_LOG(LogTemp, Log, TEXT("[ABaseTurbine] BeginOverlap, OtherActor: %s"), *OtherActor->GetName());
	UE_LOG(LogTemp, Log, TEXT("[ABaseTurbine] BeginOverlap, ThisActor: %s"), *ThisActor->GetName());

	if(OtherActor == ThisActor) return;
	if(!OtherActor->IsA(ABaseTurbine::StaticClass())) return;

	UE_LOG(LogTemp, Log, TEXT("[ABaseTurbine] BeginOverlap, overlapping!"));
	
	bIsOverlapping = true;

	SelectionMesh->SetMaterial(0, SelectionInvalidMaterial);
}

void ABaseTurbine::EndOverlap(AActor* OtherActor)
{
	if(OtherActor == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("[ABaseTurbine] EndOverlap, Other actor is null!"));
		return;
	}
	if(!OtherActor->IsA(ABaseTurbine::StaticClass())) return;
	DisableOverlap();
}

// Called when the game starts or when spawned
void ABaseTurbine::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("[BaseTurbine] BeginPlay"));

	PlacementLocation = GetActorLocation();

	DisableOverlap();
}

// Called every frame
void ABaseTurbine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurveTimeline.TickTimeline(DeltaTime);
}

void ABaseTurbine::SetSelected()
{
	DisableOverlap();
	bIsSelected = true;
	SelectionMesh->SetVisibility(true);
}

void ABaseTurbine::SetUnselected()
{
	bIsSelected = false;
	SelectionMesh->SetVisibility(false);
}

void ABaseTurbine::Place(float NewWindMultiplier)
{
	bIsInitialPlacement = false;
	TurbineEnergyController->SetEnergy(NewWindMultiplier);
	PlacementLocation = GetActorLocation();
}

bool ABaseTurbine::IsOverlapping() const
{
	return bIsOverlapping;
}

void ABaseTurbine::Move(float Value)
{
	// if(!bMove) return;
	const FVector NewLocation = FMath::Lerp(MovementStartLocation, MovementLocation, Value);
	SetActorLocation(NewLocation);
}

void ABaseTurbine::StartMovement(const FVector& TargetMovementLocation)
{
	if(CurveFloat == nullptr)
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

void ABaseTurbine::EndMovement()
{
	UE_LOG(LogTemp, Log, TEXT("[ABaseTurbine] EndMovement"));
	OnMovementComplete.Broadcast(this);
}

void ABaseTurbine::DisableOverlap()
{
	bIsOverlapping = false;
	SelectionMesh->SetMaterial(0, SelectionValidMaterial);
}

bool ABaseTurbine::IsInitialPlacement() const
{
	return bIsInitialPlacement;
}

UTurbineEnergyController* ABaseTurbine::GetEnergyController() const
{
	return TurbineEnergyController;
}

int32 ABaseTurbine::GetLevel() const
{
	return Level;
}

FVector ABaseTurbine::GetPlacementLocation() const
{
	return PlacementLocation;
}
