// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"

// Sets default values
ABuilding::ABuilding()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BuildingMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Building Mesh");
	SetRootComponent(BuildingMeshComponent);
}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABuilding::Initialize()
{
	if (BuildingMeshComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[ABuilding] %s, SetMaterialCount(), BuildingMeshComponent is null!"), *GetName());
		return;
	}

	// Store materials and materials count
	Materials = BuildingMeshComponent->GetMaterials();
	MaterialCount = Materials.Num();

	// Turn off all lights
	TurnOffLights();
}

int ABuilding::GetMaterialCount() const
{
	return MaterialCount;
}

void ABuilding::TurnOffLights()
{
	for (int i = 1; i < Materials.Num(); i++)
	{
		Materials[i] = LightOffMaterial;
		BuildingMeshComponent->SetMaterial(i, LightOffMaterial);
		OffLightIndices.Add(i);
	}
}

void ABuilding::TurnOnRandomLight(bool& IsCompletelyOn)
{
	UE_LOG(LogTemp, Log, TEXT("[ABuilding] TurnOnRandomLight()"));
	const int Index = FMath::RandRange(0, OffLightIndices.Num() - 1);
	const int MaterialIndex = OffLightIndices[Index];

	Materials[MaterialIndex] = LightOnMaterial;
	BuildingMeshComponent->SetMaterial(MaterialIndex, LightOnMaterial);

	OffLightIndices.Remove(MaterialIndex);
	OnLightIndices.Add(MaterialIndex);

	IsCompletelyOn = OffLightIndices.Num() == 0;
}

void ABuilding::TurnOffRandomLight(bool& IsCompletelyOff)
{
	const int Index = FMath::RandRange(0, OnLightIndices.Num() - 1);
	const int MaterialIndex = OnLightIndices[Index];
	
	Materials[MaterialIndex] = LightOffMaterial;
	BuildingMeshComponent->SetMaterial(MaterialIndex, LightOffMaterial);

	OffLightIndices.Add(MaterialIndex);
	OnLightIndices.Remove(MaterialIndex);

	IsCompletelyOff = OnLightIndices.Num() == 0;
}
