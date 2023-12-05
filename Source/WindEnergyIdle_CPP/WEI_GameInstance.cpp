// Fill out your copyright notice in the Description page of Project Settings.


#include "WEI_GameInstance.h"

#include "DefaultSaveGame.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"

UDefaultSaveGame* UWEI_GameInstance::GetSaveGame()
{
	if(DefaultSaveGame == nullptr)
	{
		Load();
	}
	
	return DefaultSaveGame;
}

void UWEI_GameInstance::Save()
{
	if(DefaultSaveGame == nullptr)
	{
		return;
	}

	FAsyncSaveGameToSlotDelegate SavedDelegate;
	SavedDelegate.BindUObject(this, &ThisClass::OnSaveCompleted);
	UGameplayStatics::AsyncSaveGameToSlot(DefaultSaveGame, SaveGameSlotName, UserIndex, SavedDelegate);
}

void UWEI_GameInstance::Load()
{
	const bool bDoesSaveGameExist = UGameplayStatics::DoesSaveGameExist(SaveGameSlotName, UserIndex);
	if(bDoesSaveGameExist)
	{
		USaveGame* SaveGame = UGameplayStatics::LoadGameFromSlot(SaveGameSlotName, UserIndex);
		if(SaveGame->IsA(UDefaultSaveGame::StaticClass()))
		{
			DefaultSaveGame = static_cast<UDefaultSaveGame*>(SaveGame);
		}
		else
		{
			const auto CreatedSaveGame = UGameplayStatics::CreateSaveGameObject(UDefaultSaveGame::StaticClass());
			DefaultSaveGame = static_cast<UDefaultSaveGame*>(CreatedSaveGame);
		}
	}
}

void UWEI_GameInstance::OnSaveCompleted(const FString& UsedSlotName, const int32 UsedUserIndex, bool bWasSuccessful)
{
}
