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

void ABaseTurbine::BeginOverlap(AActor* OtherActor)
{
	UE_LOG(LogTemp, Log, TEXT("[ABaseTurbine] BeginOverlap"));

	const auto ThisActor = static_cast<AActor*>(this);
	UE_LOG(LogTemp, Log, TEXT("[ABaseTurbine] BeginOverlap, OtherActor: %s"), *OtherActor->GetName());
	UE_LOG(LogTemp, Log, TEXT("[ABaseTurbine] BeginOverlap, ThisActor: %s"), *ThisActor->GetName());

	if(OtherActor == ThisActor) return;

	UE_LOG(LogTemp, Log, TEXT("[ABaseTurbine] BeginOverlap, overlapping!"));
	
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

	PlacementLocation = GetActorLocation();

	EndOverlap();
	
	SetUnselected();
}

// Called every frame
void ABaseTurbine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurveTimeline.TickTimeline(DeltaTime);
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

	WindMultiplier = 1;

	float EnergyDifference = (BaseEnergyPerSecond * WindMultiplier) - (BaseEnergyPerSecond * PreviousWindMultiplier);

	PreviousWindMultiplier = WindMultiplier;
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

bool ABaseTurbine::IsInitialPlacement() const
{
	return bIsInitialPlacement;
}

int32 ABaseTurbine::GetLevel() const
{
	return Level;
}

float ABaseTurbine::GetWindMultiplier() const
{
	return WindMultiplier;
}

FVector ABaseTurbine::GetPlacementLocation() const
{
	return PlacementLocation;
}
