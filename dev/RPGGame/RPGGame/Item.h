#pragma once
#include "AActor.h"
#include <string>

enum class ItemType
{
	Weapon,
	Armor,
	Consumable,
	Misc
};

struct ItemStruct
{
	std::string ItemName;
	std::string ItemID;
	int ItemValue = 0;
	int MaxStack = 1;
	ItemType Type = ItemType::Misc;
	
};

class Item : public AActor
{
public:
	Item(const ItemStruct& InData) : ItemData(InData) {}
	virtual void Use();

	const ItemStruct& GetData() const { return ItemData; }

protected:
	ItemStruct ItemData;
};

