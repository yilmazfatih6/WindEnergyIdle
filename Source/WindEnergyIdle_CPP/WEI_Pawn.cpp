// Fill out your copyright notice in the Description page of Project Settings.


#include "WEI_Pawn.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"

// Sets default values
AWEI_Pawn::AWEI_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

// Called when the game starts or when spawned
void AWEI_Pawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWEI_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	HoverSelectedTurbine();
}

// Called to bind functionality to input
void AWEI_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	// Clear out existing mapping, and add our mapping
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	// Get the EnhancedInputComponent
	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	// Bind the actions
	PEI->BindAction(InputAction, ETriggerEvent::Started, this, &AWEI_Pawn::OnLeftMouseClickPressed);
	PEI->BindAction(InputAction, ETriggerEvent::Completed, this,  &AWEI_Pawn::OnLeftMouseClickRelease);
}

void AWEI_Pawn::OnLeftMouseClickPressed()
{
	UE_LOG(LogTemp, Log, TEXT("OnLeftMouseClickPressed"));

	bIsLeftMouseDown = true;
	SelectTurbine();
}

void AWEI_Pawn::OnLeftMouseClickRelease()
{
	UE_LOG(LogTemp, Log, TEXT("OnLeftMouseClickRelease"));

	bIsLeftMouseDown = false;
	PlaceSelectedTurbine();
}

void AWEI_Pawn::SpawnTurbine(bool &bWasSuccessful)
{
	if (!bIsSpawnedPlaced)
	{
		bWasSuccessful = false;
		return;
	}

	bWasSuccessful = true;
	bIsSpawnedPlaced = false;
	ABaseTurbine* SpawnedTurbine = GetWorld()->SpawnActor<ABaseTurbine>(TurbineToSpawn, SpawnLocation, SpawnRotation);
	SetTurbineSelected(SpawnedTurbine);
	UE_LOG(LogTemp, Log, TEXT("[WEI_Pawn] SpawnTurbine, Turbine: %s"), *SpawnedTurbine->GetName());

	OnTurbineSpawned.Broadcast();
}

void AWEI_Pawn::PlaceSelectedTurbine()
{
	if(!SelectedTurbine) return;

	SelectedTurbine->SetUnselected();

	if(SelectedTurbine->IsOverlapping())
	{
		PlacementLocation = SelectedTurbine->GetActorLocation();
		bMoveToPickupLocation = true;
	}

	PreviouslySelectedTurbine = SelectedTurbine;
	SelectedTurbine = nullptr;

	bIsSpawnedPlaced = true;

	UE_LOG(LogTemp, Log, TEXT("[WEI_Pawn] PlaceSelectedTurbine, Turbine: %s"), *PreviouslySelectedTurbine->GetName());
}

void AWEI_Pawn::MoveBackToPickupLocation()
{
	if(!bMoveToPickupLocation) return;

	if(!PreviouslySelectedTurbine) return;

	// SelectedTurbine->SetActorLocation()

	// Create a timer
	FTimerHandle TimerHandle;

	// Create a delegate that will call the FInterpTo function
	const FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &AWEI_Pawn::MoveToPickUpLocation);

	// Set the timer to call the delegate at a specified interval
	GetWorldTimerManager().SetTimer(TimerHandle, Delegate, 0.1f, true);
}

void AWEI_Pawn::MoveToPickUpLocation() const
{
	if(!SelectedTurbine) return;
	if(!PreviouslySelectedTurbine) return;
	
	PreviouslySelectedTurbine->SetActorLocation(FMath::Lerp(SelectedTurbine->GetActorLocation(), PickupLocation, GetWorld()->DeltaTimeSeconds * MovementSpeed));
	// SelectedTurbine->SetActorLocation(PickupLocation);
}

void AWEI_Pawn::SetTurbineSelected(ABaseTurbine* Turbine)
{
	SelectedTurbine = Turbine;
	SelectedTurbine->SetSelected();
	PickupLocation = SelectedTurbine->GetActorLocation();
	UE_LOG(LogTemp, Log, TEXT("[WEI_Pawn] SetTurbineSelected, Turbine: %s"), *SelectedTurbine->GetName());
}

void AWEI_Pawn::HoverSelectedTurbine()
{
	if(!bIsLeftMouseDown) return;

	if(!SelectedTurbine) return;

	PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	const FVector TraceEnd = WorldLocation + WorldDirection * TraceDistance;

	QueryParams.AddIgnoredActor(this);
	
	GetWorld()->LineTraceSingleByChannel(Hit, WorldLocation, TraceEnd, TraceChannelPropertyGround, QueryParams);
	// DrawDebugLine(GetWorld(), WorldLocation, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);

	if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
	{
		// UE_LOG(LogTemp, Log, TEXT("Trace hit actor: %s"), *Hit.GetActor()->GetName());
		SelectedTurbine->SetActorLocation(Hit.ImpactPoint);
	}
	else {
		// UE_LOG(LogTemp, Log, TEXT("No Actors were hit"));
	}

	UE_LOG(LogTemp, Log, TEXT("[WEI_Pawn] HoverSelectedTurbine, Turbine: %s"), *SelectedTurbine->GetName());
}

void AWEI_Pawn::SelectTurbine()
{
	if(!bIsLeftMouseDown) return;
	if(!bIsSpawnedPlaced) return;

	bMoveToPickupLocation = false;

	PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	const FVector TraceEnd = WorldLocation + WorldDirection * TraceDistance;

	QueryParams.AddIgnoredActor(this);

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

	SetTurbineSelected(HitTurbine);
}


