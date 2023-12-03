// Fill out your copyright notice in the Description page of Project Settings.


#include "Ground.h"

#include "WEI_Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "WindEnergyIdle_CPP/PawnComponents/TurbinePlacer.h"
#include "WindEnergyIdle_CPP/PawnComponents/TurbineSelector.h"

// Sets default values
AGround::AGround()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGround::BeginPlay()
{
	Super::BeginPlay();

	const auto Material = StaticMeshComponent->GetMaterial(0);
	MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(Material, this);

	OnTimelineUpdate.BindDynamic(this, &ThisClass::OnTimelineUpdated);
	OnTimelineFinish.BindDynamic(this, &ThisClass::OnTimelineFinished);

	CurveTimeline.AddInterpFloat(CurveFloat, OnTimelineUpdate);
	CurveTimeline.SetTimelineFinishedFunc(OnTimelineFinish);
	CurveTimeline.SetLooping(false);

	StaticMeshComponent->SetMaterial(0, MaterialInstanceDynamic);

	auto Pawn = static_cast<AWEI_Pawn*>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	Pawn->GetTurbineSelector()->OnSelect.AddDynamic(this, &ThisClass::OnTurbineSelected);
	Pawn->GetTurbinePlacer()->OnPlacementSucceed.AddDynamic(this, &ThisClass::OnTurbinePlaced);
	Pawn->GetTurbinePlacer()->OnPlacementFail.AddDynamic(this, &ThisClass::OnTurbinePlaced);
}

// Called every frame
void AGround::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurveTimeline.TickTimeline(DeltaTime);
}

void AGround::OnTurbineSelected(ABaseTurbine* Turbine)
{
	UE_LOG(LogTemp, Log, TEXT("[AGround] OnTurbineSelected"));
	EnableWindMap();
}

void AGround::OnTurbinePlaced(ABaseTurbine* Turbine)
{
	UE_LOG(LogTemp, Log, TEXT("[AGround] OnTurbinePlaced"));
	DisableWindMap();
}

void AGround::EnableWindMap()
{
	UE_LOG(LogTemp, Log, TEXT("[AGround] EnableWindMap"));

	CurveTimeline.PlayFromStart();
}

void AGround::DisableWindMap()
{
	UE_LOG(LogTemp, Log, TEXT("[AGround] DisableWindMap"));
	CurveTimeline.Reverse();
}

void AGround::OnTimelineUpdated(float Value)
{
	MaterialInstanceDynamic->SetScalarParameterValue("WindMapAlpha", Value);
}

void AGround::OnTimelineFinished()
{
}

float AGround::GetWindMapValue_Implementation(FHitResult HitResult)
{
	UE_LOG(LogTemp, Log, TEXT("[AGround] GetWindMapValue_Implementation"));
	return 1.f;
}
