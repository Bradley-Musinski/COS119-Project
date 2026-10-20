#pragma once
#include <string>
#include <vector>
#include "UMath.h"

struct CharacterAbility
{
	std::string Name;
	std::string Desc;
	int MinDamage = 0; // Damage dealth to the target
	int MaxDamage = 0;
	int Health = 0; // Health resortation to the user
	int Armor = 0;
	int cost = 0; // Mana for spell casters, stamina for martial classes

};

inline const std::vector<CharacterAbility> WarlockAbilities =
{
	{"Eldritch Blast", "A Crackling beam of dark energy", 12, 16, 0, 0, 5},
	{"Hex", "A whispered curse that makes the target suffer with every turn", 5, 9, 0, 0, 2},
	{"Armor of Agathys", "A spectral frost coats the caster, shielding them and chilling any who strike", 0, 0, 0, 2, 5},
	{"Patron's Wrath", "The unknown patron answers, unleashing a torrent of shadow", 14, 22, 0, 0, 10}
};

inline const std::vector<CharacterAbility> SoldierAbilities =
{
	{"Power Strike", "A heavy, two-handed swing that cleaves through armor", 12, 16, 0, 0, 5},
	{"Shield Bash", "Slams the enemy with a shield, leaving them reeling", 16, 0, 0, 0, 3},
	{"Rallying Cry", "A battle shout that steels the Soldier's resolve and mends wounds", 0, 0, 8, 2, 4},
	{"Relentless Assault", "A furious flurry of strikes that gives the enemy no room to breathe", 14, 22, 0, 0, 9}
};