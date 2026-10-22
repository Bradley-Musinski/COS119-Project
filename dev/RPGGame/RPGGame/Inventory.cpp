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
	const size_t MaxItems = 20;

	if (Items.size() >= MaxItems)
	{
		return false;   // bag is full
	}

	Items.push_back(NewItem);
	return true;
}

bool Inventory::RemoveItem(const Item& ItemToRemove)
{
	for (Item& slot : Items)
	{
		if (slot.ItemData.ItemID == ItemToRemove.ItemData.ItemID)
		{
			slot = Item();   // reset to empty
			return true;
		}
	}
	return false;
}
