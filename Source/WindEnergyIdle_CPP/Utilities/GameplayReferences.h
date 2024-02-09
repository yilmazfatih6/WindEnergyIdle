#pragma once

#include "GameplayReferences.generated.h"

UCLASS()
class WINDENERGYIDLE_CPP_API UGameplayReferences : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static class AWEI_Pawn* GetWEIPawn(const UObject* WorldContextObject);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static class AWEI_GM* GetWEIGameMode(const UObject* WorldContextObject);
};
