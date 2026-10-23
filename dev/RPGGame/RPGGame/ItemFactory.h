#pragma once
#include "Item.h"

namespace ItemFactory
{
	inline Item HealthPotion()
	{
		Item item;
		item.ItemData.ItemName = "Health Potion";
		item.ItemData.ItemID = 1;
		item.ItemData.ItemValue = 50;
		item.ItemData.bIsStackable = true;
		item.ItemData.MaxStack = 999;
		item.ItemData.NumStack = 0;
		item.ItemData.Type = ItemType::Consumable;
		item.ItemData.Amount = 50;
		return item;
	}
};

