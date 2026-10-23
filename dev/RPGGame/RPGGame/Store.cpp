#include "Store.h"
#include "GameEngine.h"
#include "ItemFactory.h"
#include "Input.h"

void Store::OpenStore(Player& player)
{
	while (true)
	{
		GEngine->ClearConsole();

		Item potion = ItemFactory::HealthPotion();
		int price = potion.ItemData.ItemValue;

		GEngine->Print("<=><=><=> STORE <=><=><=>", Color::Gold, 2);
		GEngine->Print("Gold: " + std::to_string(player.character.GetGold()), Color::Gold, 2);

		GEngine->Print("1. " + potion.ItemData.ItemName + " | " + std::to_string(price) + " gold | Restores " + std::to_string(potion.ItemData.Amount) + "hp", Color::White, 1);
		GEngine->Print("2. Leave Store", Color::White, 2);

		int choice = Input::GetInput(">> ", 1, 2);

		if (choice == 2)
		{
			return; // back to the town
		}

		if (choice == 1)
		{
			// Not enough gold
			if (player.character.GetGold() < price)
			{
				GEngine->Print(":: You don't have enough gold! ::", Color::Red, 1);
			}
			// Bag is full
			else if (!player.character.Additem(potion))
			{
				GEngine->Print(":: Your bag is full! ::", Color::Red, 1);
			}
			// Bought it
			else
			{
				player.character.SetGold(player.character.GetGold() - price);
				GEngine->Print(":: You bought a " + potion.ItemData.ItemName + "! ::", Color::Green, 1);
			}

			GEngine->WaitForKey();
		}
	}
}