// Fill out your copyright notice in the Description page of Project Settings.
#include "WEI_Pawn.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "WindEnergyIdle_CPP/Components/PawnComponents/TurbineMerger.h"
#include "WindEnergyIdle_CPP/Components/PawnComponents/TurbinePlacer.h"
#include "WindEnergyIdle_CPP/Components/PawnComponents/TurbineSelector.h"
#include "WindEnergyIdle_CPP/Components/PawnComponents/TurbineSpawner.h"

// Sets default values
AWEI_Pawn::AWEI_Pawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	TurbineSpawner = CreateDefaultSubobject<UTurbineSpawner>(TEXT("Turbine Spawner"));
	TurbinePlacer = CreateDefaultSubobject<UTurbinePlacer>(TEXT("Turbine Placer"));
	TurbineSelector = CreateDefaultSubobject<UTurbineSelector>(TEXT("Turbine Selector"));
	TurbineMerger = CreateDefaultSubobject<UTurbineMerger>(TEXT("Turbine Merger"));
	TurbineMerger->InjectData(TurbineSpawner, TurbinePlacer, TurbineSelector);
}

// Called when the game starts or when spawned
void AWEI_Pawn::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
	{
		UE_LOG(LogTemp, Warning, TEXT("This text will appear in the console 3 seconds after execution"));
		if(TurbineSpawner == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("[AWEI_Pawn] TurbineSpawner is nullptr!"))
		}
		else
		{
			TurbineSpawner->OnSpawnComplete.AddDynamic(this, &ThisClass::OnTurbineSpawned);
		}

		if(TurbineSelector == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("[AWEI_Pawn] TurbineSelector is nullptr!"))
		}
		else
		{
			TurbineSelector->OnSelect.AddDynamic(this, &ThisClass::OnTurbineSelected);
		}
	
		if(TurbinePlacer == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("[AWEI_Pawn] TurbinePlacer is nullptr!"))
		}
		else
		{
			TurbinePlacer->OnPlacementSucceed.AddDynamic(this, &ThisClass::OnTurbinePlaced);
			TurbinePlacer->OnPlacementFail.AddDynamic(this, &ThisClass::OnTurbinePlacementFailed);
		}
	}, .5f, false);
}

// Called every frame
void AWEI_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AWEI_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		PlayerController->GetLocalPlayer());

	// Clear out existing mapping, and add our mapping
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	// Get the EnhancedInputComponent
	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// Bind the actions
	PEI->BindAction(InputAction, ETriggerEvent::Started, this, &AWEI_Pawn::OnLeftMouseClickPressed);
	PEI->BindAction(InputAction, ETriggerEvent::Completed, this, &AWEI_Pawn::OnLeftMouseClickRelease);
}

void AWEI_Pawn::OnLeftMouseClickPressed()
{
	UE_LOG(LogTemp, Log, TEXT("[WEI_Pawn] OnLeftMouseClickPressed"));

	bIsLeftMouseDown = true;
	TurbineSelector->LineTraceTurbine();
	TurbinePlacer->SetHover(true);
}

void AWEI_Pawn::OnLeftMouseClickRelease()
{
	// UE_LOG(LogTemp, Log, TEXT("OnLeftMouseClickRelease"));
	bIsLeftMouseDown = false;
	TurbinePlacer->Place();
	TurbinePlacer->SetHover(false);
}

UTurbineSelector* AWEI_Pawn::GetTurbineSelector()
{
	return TurbineSelector;
}

UTurbinePlacer* AWEI_Pawn::GetTurbinePlacer()
{
	return TurbinePlacer;
}

void AWEI_Pawn::OnTurbineSpawned(ATurbine* Turbine)
{
	UE_LOG(LogTemp, Log, TEXT("[WEI_Pawn] OnTurbineSpawned"));
	TurbineSelector->SetSelectedTurbine(Turbine);
}

void AWEI_Pawn::OnTurbineSelected(ATurbine* Turbine)
{
	TurbinePlacer->SetTargetTurbine(Turbine);
}

void AWEI_Pawn::OnTurbinePlaced(ATurbine* Turbine)
{
	TurbineSpawner->SetCanSpawn(true);
	TurbineSelector->ResetSelectedTurbine();
}

void AWEI_Pawn::OnTurbinePlacementFailed(ATurbine* Turbine)
{
	if (Turbine->IsInitialPlacement())
	{
		return;
	}
	TurbineSelector->ResetSelectedTurbine();
}
