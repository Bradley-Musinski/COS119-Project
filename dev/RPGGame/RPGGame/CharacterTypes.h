#pragma once
#include <iostream>
#include <vector>
#include "Abilties.h"

struct CharacterTypes
{
	std::string Name;
	std::string Desc;
	int Health = 0;
	int Attack = 0;
	int ArmorClass = 0;
	int Stamina = 0;
	std::vector<CharacterAbility> charAbilties;
};

inline const CharacterTypes Warlock{ "Warlock", "\033[3m\033[90mBound by a pact with an unknown patron, the Warlock trades safety for devastating dark magic.\033[0m", 100, 12, 4, 15, WarlockAbilities};
inline const CharacterTypes Soldier{ "Soldier", "\033[3m\033[90mA battle-hardened fighter who trusts in steel, discipline, and the grit to outlast any foe.\033[0m", 120, 16, 6, 20, SoldierAbilities };
