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
	for (Item& slot : Items)
	{
		if (bIsEmpty())
		{
			slot = NewItem;
			return true;
		}
	}

	return false;   // inventory full
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
