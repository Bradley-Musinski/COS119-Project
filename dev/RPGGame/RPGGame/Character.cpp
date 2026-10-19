#include <iostream>
#include <string>
#include <vector>
#include "AActor.h"
#include "UMath.h"
#include "Character.h"
#include "GameEngine.h"
#include "Screens.h"
#include "Abilties.h"

int Character::RollInitiative()
{
	initiative = UMath::RandRange(1, 20);
	return initiative;
}


void Character::PrintStats() const
{}

bool Character::IsAlive(const Character * character) const
{
	return character->charStats.Health > 0;
}

bool Character::AnyAlive(const std::vector<Character*>& characters) const
{
	for (const Character* c : characters)
	{
		if (IsAlive(c))
		{
			return true;
		}
	}

	return false;
}

