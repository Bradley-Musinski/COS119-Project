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

void Character::Attack(Character* attacker, Character* target, int damage)
{
	target->charStats.Health = UMath::Clamp(target->charStats.Health - damage, 0, target->charStats.MaxHealth);

	GEngine->TypeOut(attacker->charStats.Name + " attacks " + target->charStats.Name
		+ " for " + std::to_string(damage) + " damage!", 15ms, 500ms, Color::Gray, 1);

	GEngine->Print(target->charStats.Name + " " + "Health: " + std::to_string(target->charStats.Health), Color::White, 1);

	if (!target->IsAlive())
	{
		GEngine->TypeOut(target->charStats.Name + " has been defeated!", 15ms, 500ms, Color::Red, 1);
	}
}

bool Character::RollToHit(const Character* target) const
{
	int roll = UMath::RandRange(1, 20);

	if (roll == 1)
	{
		return false; // natural 1 always misses
	}
	if (roll == 20)
	{
		return true;  // natural 20 always hits
	}

	return roll >= target->charStats.ArmorClass;
}

bool Character::IsAlive() const
{
	return charStats.Health > 0;
}

bool Character::AnyAlive(const std::vector<Character*>& characters)
{
	for (const Character* c : characters)
	{
		if (c->IsAlive())
		{
			return true;
		}
	}

	return false;
}

void Character::PrintStats() const
{}
