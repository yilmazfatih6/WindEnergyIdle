// Fill out your copyright notice in the Description page of Project Settings.

#include "Turbine.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "WindEnergyIdle_CPP/Components/PawnComponents/TurbineSpawner.h"
#include "WindEnergyIdle_CPP/Components/TurbineComponents/TurbineEnergyController.h"
#include "WindEnergyIdle_CPP/Core/WEI_GM.h"
#include "WindEnergyIdle_CPP/Core/WEI_Pawn.h"
#include "WindEnergyIdle_CPP/DataAssets/TurbineDataAsset.h"
#include "WindEnergyIdle_CPP/DataContainers/TurbinePlacementData.h"
#include "WindEnergyIdle_CPP/Managers/IncomeManager.h"
#include "WindEnergyIdle_CPP/Utilities/GameplayReferences.h"

// Sets default values
ATurbine::ATurbine()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurbineEnergyController = CreateDefaultSubobject<UTurbineEnergyController>(TEXT("Energy Controller"));
	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotating Movement Component"));
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	PropellerRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Propeller Root"));
	PlacementStatusMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Placement Status Mesh"));
	TurbineBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turbine Body Mesh"));
	TurbinePropellerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turbine Propeller Mesh"));

	SetRootComponent(RootSceneComponent);
	CapsuleComponent->SetupAttachment(RootSceneComponent);
	PropellerRoot->SetupAttachment(CapsuleComponent);
	PlacementStatusMesh->SetupAttachment(CapsuleComponent);
	TurbineBodyMesh->SetupAttachment(CapsuleComponent);
	TurbinePropellerMesh->SetupAttachment(PropellerRoot);
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

	if(PlacementStatusMesh == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[ABaseTurbine] SelectionMesh is null!"));
		return;
	}
	PlacementStatusMesh->SetMaterial(0, SelectionInvalidMaterial);
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

void ATurbine::OnBoostRatioChanged(float Value)
{
	BoostRatio = Value;
	SetPropellerRotationRate();
}

// Called when the game starts or when spawned
void ATurbine::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("[ATurbine] BeginPlay"));

	PlacementLocation = GetActorLocation();

	DisableOverlap();

	RotatingMovementComponent->SetUpdatedComponent(PropellerRoot);
	
	DefaultRotationRate = RotatingMovementComponent->RotationRate;

	WEI_Pawn = UGameplayReferences::GetWEIPawn(GetWorld());

	GameMode = UGameplayReferences::GetWEIGameMode(GetWorld());
	
	GameMode->IncomeManager->OnBoostRatioChanged.AddDynamic(this, &ThisClass::OnBoostRatioChanged);
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
	if(PlacementStatusMesh == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[ABaseTurbine] SelectionMesh is null!"));
		return;
	}
	PlacementStatusMesh->SetVisibility(true);
}

void ATurbine::SetUnselected()
{
	bIsSelected = false;
	if(PlacementStatusMesh == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[ABaseTurbine] SelectionMesh is null!"));
		return;
	}
	PlacementStatusMesh->SetVisibility(false);
}

void ATurbine::Place()
{
	if(bIsInitialPlacement)
	{
		WEI_Pawn->GetTurbineSpawner()->AddToTurbinesByLevels(this, Level);
	}
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

	if(PlacementStatusMesh == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[ABaseTurbine] SelectionMesh is null!"));
		return;
	}
	
	PlacementStatusMesh->SetMaterial(0, SelectionValidMaterial);
}

bool ATurbine::IsInitialPlacement() const
{
	return bIsInitialPlacement;
}

UTurbineEnergyController* ATurbine::GetEnergyController() const
{
	return TurbineEnergyController;
}

int32 ATurbine::GetTurbineLevel() const
{
	return Level;
}

FVector ATurbine::GetPlacementLocation() const
{
	return PlacementLocation;
}

float ATurbine::GetWindMapValue() const
{
	return WindMapValue;
}

void ATurbine::SetWindMapValue(float Value)
{
	WindMapValue = Value;
	SetPropellerRotationRate();
}

void ATurbine::SetPropellerRotationRate()
{
	const auto Rate = (Data->GetBoostRotationMultiplier() * BoostRatio + 1) * Data->GetRotationMultiplier() * WindMapValue * DefaultRotationRate;
	// UE_LOG(LogTemp, Log, TEXT("[ATurbine] SetPropellerRotationRate(), BoostRatio = %f"), BoostRatio);
	// UE_LOG(LogTemp, Log, TEXT("[ATurbine] SetPropellerRotationRate(), BoostRotationMultiplier = %f"), Data->GetBoostRotationMultiplier());
	// UE_LOG(LogTemp, Log, TEXT("[ATurbine] SetPropellerRotationRate(), RotationSpeedMultiplier = %f"), Data->GetRotationMultiplier());
	// UE_LOG(LogTemp, Log, TEXT("[ATurbine] SetPropellerRotationRate(), WindMapValue = %f"), WindMapValue);
	// UE_LOG(LogTemp, Log, TEXT("[ATurbine] SetPropellerRotationRate(), DefaultRotationRate = %f, %f, %f"), DefaultRotationRate.Roll, DefaultRotationRate.Pitch, DefaultRotationRate.Yaw);
	// UE_LOG(LogTemp, Log, TEXT("[ATurbine] SetPropellerRotationRate(), Rate = %f, %f, %f"), Rate.Roll, Rate.Pitch, Rate.Yaw);
	RotatingMovementComponent->RotationRate = Rate;
				
}
