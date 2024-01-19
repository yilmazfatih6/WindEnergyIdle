#include "GameplayReferences.h"

#include "Kismet/GameplayStatics.h"
#include "WindEnergyIdle_CPP/Core/WEI_GM.h"
#include "WindEnergyIdle_CPP/Core/WEI_Pawn.h"

AWEI_Pawn* GameplayReferences::GetWEIPawn(const UObject* WorldContextObject)
{
	const auto Pawn = UGameplayStatics::GetPlayerPawn(WorldContextObject, 0);
	if(Pawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[GameplayReferences] GetWEIGameMode(), Pawn is null!"));
		return nullptr;
	}
	
	const auto WEI_Pawn = Cast<AWEI_Pawn>(Pawn);
	if(WEI_Pawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[GameplayReferences] GetWEIGameMode(), WEI_Pawn is null!"));
		return nullptr;
	}
	return WEI_Pawn;
}

AWEI_GM* GameplayReferences::GetWEIGameMode(const UObject* WorldContextObject)
{
	const auto GM = UGameplayStatics::GetGameMode(WorldContextObject);
	if(GM == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[GameplayReferences] GetWEIGameMode(), GameMode is null!"));
		return nullptr;
	}

	const auto GameMode = Cast<AWEI_GM>(GM);
	if(GameMode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[GameplayReferences] GetWEIGameMode(), WEI GameMode is null!"));
		return nullptr;
	}

	return GameMode;
}
