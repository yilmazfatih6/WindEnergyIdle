// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTurbine.h"

#include "EnergyManager.h"
#include "WindEnergyIdle_CPPGameModeBase.h"

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

	EndOverlap();
	
	SetUnselected();
}

// Called every frame
void ABaseTurbine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	
}

bool ABaseTurbine::IsOverlapping() const
{
	return bIsOverlapping;
}

