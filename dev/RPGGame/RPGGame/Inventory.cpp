#include "Inventory.h"

Item* Inventory::GetItem(const std::string& ItemName)
{
	for (Item& item : Items)
	{
		if (item.ItemData.ItemName == ItemName)
		{
			return &item;
		}
	}

	return nullptr;
}

bool Inventory::Additem(const Item& NewItem)
{
	const int MaxItems = 20;

	// If it stacks and we already have one, just add to the count
	if (NewItem.ItemData.bIsStackable)
	{
		for (Item& item : Items)
		{
			if (item.ItemData.ItemID == NewItem.ItemData.ItemID)
			{
				item.ItemData.NumStack += 1;
				return true;
			}
		}
	}

	if (Items.size() >= MaxItems)
	{
		return false;   // bag is full
	}

	Item item = NewItem;
	item.ItemData.NumStack = 1;
	Items.push_back(item);
	return true;
}

bool Inventory::RemoveItem(const Item& ItemToRemove)
{
	for (int i = 0; i < Items.size(); i++)
	{
		if (Items[i].ItemData.ItemID == ItemToRemove.ItemData.ItemID)
		{
			Items[i].ItemData.NumStack -= 1;

			if (Items[i].ItemData.NumStack <= 0)
			{
				Items.erase(Items.begin() + i);
			}

			return true;
		}
	}
	return false;
}
