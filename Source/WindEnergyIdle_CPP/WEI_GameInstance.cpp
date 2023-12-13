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
	UGameplayStatics::AsyncSaveGameToSlot(DefaultSaveGame, "Save Game", 0, SavedDelegate);
}

void UWEI_GameInstance::Load()
{
	const bool bDoesSaveGameExist = UGameplayStatics::DoesSaveGameExist("Save Game", 0);
	if(bDoesSaveGameExist)
	{
		USaveGame* SaveGame = UGameplayStatics::LoadGameFromSlot("Save Game", 0);
		if(SaveGame->IsA(UDefaultSaveGame::StaticClass()))
		{
			DefaultSaveGame = static_cast<UDefaultSaveGame*>(SaveGame);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("[UWEI_GameInstance] Created Save Game is not type of UDefaultSaveGame"));
		}
	}
	else
	{
		const auto CreatedSaveGame = UGameplayStatics::CreateSaveGameObject(UDefaultSaveGame::StaticClass());
		DefaultSaveGame = static_cast<UDefaultSaveGame*>(CreatedSaveGame);
	}
}

void UWEI_GameInstance::OnSaveCompleted(const FString& UsedSlotName, const int32 UsedUserIndex, bool bWasSuccessful)
{
}
