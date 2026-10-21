#pragma once
#include "GameEngine.h"
#include "UMath.h"
#include "AActor.h"
#include "Character.h"
#include "Item.h"
#include "Inventory.h"
#include "Screens.h"
#include "Abilties.h"

struct CharacterStats
{
	std::string Name = "";
	std::string ClassName = "";
	int Health = 0;
	int Attack = 0;
	int MaxHealth = 0;
	int ArmorClass = 0;
	int Stamina = 0;
	int Exp = 0;
};

class Character : public AActor
{
public:
	CharacterStats charStats;

	Character() = default;

	Character(std::string _name, std::string _classname, int _health, int _attack, int _armorClass, int _stamina, int _exp)
	{
		charStats.Name = _name;
		charStats.ClassName = _classname;
		charStats.Health = charStats.MaxHealth;
		charStats.MaxHealth = _health;
		charStats.Attack = _attack;
		charStats.ArmorClass = _armorClass;
		charStats.Stamina = _stamina;
		charStats.Exp = _exp;
	}

	int RollInitiative();
	int Initiative() const { return initiative; }

	void Attack(Character* attacker, Character* target, int damage);
	bool RollToHit(const Character* target) const;

	virtual void PrintStats() const;

	std::string Name() const { return charStats.Name; }
	void Name(std::string _name) { charStats.Name = _name; }

	bool IsAlive() const;
	static bool AnyAlive(const std::vector<Character*>& characters) ;

	Inventory character;

private:
	int initiative = 0;
};

