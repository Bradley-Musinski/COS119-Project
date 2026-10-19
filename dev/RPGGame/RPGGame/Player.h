#pragma once
#include <vector>
#include "Character.h"
#include "Abilties.h"

struct CharacterAbilities
{
	std::vector< CharacterAbility> abilities;
};

struct PlayerLeaderboard
{
	int TotalWins = 0;
	int TotalLoss = 0;
	int TotalDamageGiven = 0;
	int TotalDamageTaken = 0;
};

class Player : public Character
{
public:
	CharacterAbilities charAbilities;
	PlayerLeaderboard playerLeaderboard;

	Player() 
	{
		GEngine->RegisterActor(this);
	};

	void PrintStats() const override;

private:


};

