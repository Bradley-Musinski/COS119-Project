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
	std::string ItemName = "";
	int ItemID = 0;
	int ItemValue = 0;
	bool bIsStackable = false;
	int MaxStack = 0;
	int NumStack = 0;
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

	Item(std::string _ItemName, int _ItemID, int _ItemValue, bool _bIsStackable, int _MaxStack, int _NumStack, ItemType _Type)
	{
		ItemData.ItemName = _ItemName;
		ItemData.ItemID = _ItemID;
		ItemData.ItemValue = _ItemValue;
		ItemData.bIsStackable = _bIsStackable;
		ItemData.MaxStack = _MaxStack;
		ItemData.NumStack = _NumStack;
		ItemData.Type = _Type;
	}


	virtual void UseItem(Item& item);

};

