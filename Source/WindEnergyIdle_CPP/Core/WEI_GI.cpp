// Fill out your copyright notice in the Description page of Project Settings.


#include "WEI_GI.h"

#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "WindEnergyIdle_CPP/Systems/DefaultSaveGame.h"
#include "WindEnergyIdle_CPP/Systems/MapLoader.h"

UWEI_GI::UWEI_GI()
{
	SaveGameSlotName = "SaveGameExample";
	CurrentMapLoader = CreateDefaultSubobject<UMapLoader>("Map Loader");
}

void UWEI_GI::Init()
{
	Super::Init();
	
	const FIntPoint Resolution = FIntPoint(540, 960);
	const auto GameUserSettings = UGameUserSettings::GetGameUserSettings();
	GameUserSettings->SetScreenResolution(Resolution);
	GameUserSettings->ApplySettings(false);

	LoadGame();

	UE_LOG(LogTemp, Log, TEXT("Load Current Level"));
	CurrentMapLoader->InjectData(this, LevelList, SaveGameObject);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
	{
		CurrentMapLoader->LoadCurrentLevel();
		UE_LOG(LogTemp, Warning, TEXT("This text will appear in the console 3 seconds after execution"))
	}, 1, false);
	
}

void UWEI_GI::LoadGame()
{
	USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(SaveGameSlotName, 0);
	SaveGameObject = Cast<UDefaultSaveGame>(LoadedGame);

	UE_LOG(LogTemp, Log, TEXT("Trying to load a saved game."));

	if (!SaveGameObject)
	{
		UE_LOG(LogTemp, Log, TEXT("No saved games found. Trying to save a new one."));

		SaveGameObject = Cast<UDefaultSaveGame>(UGameplayStatics::CreateSaveGameObject(UDefaultSaveGame::StaticClass()));
		const bool IsSaved = UGameplayStatics::SaveGameToSlot(SaveGameObject, SaveGameSlotName, 0);

		LogIfGameWasSavedOrNot(IsSaved);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Saved game found. Loaded."));
	}
    
}

void UWEI_GI::SaveGame()
{
	UE_LOG(LogTemp, Log, TEXT("Saving game..."));

	const bool IsSaved = UGameplayStatics::SaveGameToSlot(SaveGameObject, SaveGameSlotName, 0);

	LogIfGameWasSavedOrNot(IsSaved);
    
}

void UWEI_GI::LogIfGameWasSavedOrNot(const bool IsSaved)
{
	if (IsSaved)
	{
		UE_LOG(LogTemp, Log, TEXT("Game saved."));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Cannot save the game."));
	}
}