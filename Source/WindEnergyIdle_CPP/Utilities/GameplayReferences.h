#pragma once

class GameplayReferences
{
public:
	static class AWEI_Pawn* GetWEIPawn(const UObject* WorldContextObject);
	static class AWEI_GM* GetWEIGameMode(const UObject* WorldContextObject);
};
