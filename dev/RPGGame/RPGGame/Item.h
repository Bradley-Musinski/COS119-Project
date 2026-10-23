#pragma once
#include "AActor.h"
#include <string>

class Character;

enum class ItemType
{
	Weapon,
	Armor,
	Consumable,
	Misc
};

struct ItemStruct
{
	std::string ItemName = "";
	int ItemID = 0;
	int ItemValue = 0;
	bool bIsStackable = false;
	int MaxStack = 0;
	int NumStack = 0;
	int Amount = 0;
	ItemType Type = ItemType::Misc;
	
};

class Item : public AActor
{
public:
	ItemStruct ItemData;

	Item()
	{
		ItemData.ItemName = "";
		ItemData.ItemID = 0;
		ItemData.ItemValue = 0;
		ItemData.bIsStackable = false;
		ItemData.MaxStack = 0;
		ItemData.NumStack = 0;
		ItemData.Type = ItemType::Misc;
	}

	void UseItem(Character& character);

};

