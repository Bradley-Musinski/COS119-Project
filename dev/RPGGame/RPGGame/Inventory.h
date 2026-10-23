#pragma once
#include <vector>
#include "AActor.h"
#include "Item.h"

class Inventory : public AActor
{
public:
	Item ItemData;

	Inventory()
	{
		Gold = 0;
	}

	Item* GetItem(const std::string& ItemName);
	bool Additem(const Item& _Item);
	bool RemoveItem(const Item& ItemToRemove);
	bool bIsEmpty() const { return ItemData.ItemData.ItemID == 0; }

	std::vector<Item> GetItems()
	{
		return Items;
	}

	int GetGold() const { return Gold; }
	void SetGold(int _Gold) { Gold = _Gold; }

	std::vector<Item> Items;
	int Gold;

};

