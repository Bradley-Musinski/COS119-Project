#include "Town.h"
#include "GameEngine.h"
#include "GameSession.h"
#include "Input.h"
#include "SaveSystem.h"
#include "UMath.h"
#include "Player.h"
#include "Store.h"

Town::Town(GameSession& _session, Player& _player)
	: session(_session), player(_player)
{}

void Town::TownArea()
{
	bSafeZone = true; // reset every time we enter town
	
	// Pick a name once and keep it for later visits
	if (currentTownName.empty())
	{
		if (townNames.empty())
		{
			currentTownName = "Unnamed Town";
		}
		else
		{
			int lastIndex = static_cast<int>(townNames.size()) - 1;
			currentTownName = townNames[UMath::RandRange(0, lastIndex)];
		}
	}

	PrintMenu();

	while (bSafeZone)
	{
		int userInput = Input::GetInput(">> ", 1, 6);

		switch (userInput)
		{
		case 1: // Shop - needs the inventory system first
			Store store;
			store.OpenStore(player);
			PrintMenu();
			break;
		case 2:
			LongRest(player);
			GEngine->ClearLastLine(2);
			break;
		case 3:
		{
			const std::vector<Item>& ItemList = player.character.GetItems();

			GEngine->Print("Gold: " + std::to_string(player.character.GetGold()), Color::Gold, 1);

			if (ItemList.empty())
			{
				GEngine->Print("Your inventory is empty.", Color::White, 1);
			}
			else
			{
				for (int i = 0; i < ItemList.size(); i++)
				{
					std::string LastItemName = ItemList[i].ItemData.ItemName;

					GEngine->Print(ItemList[i].ItemData.ItemName + " | " + std::to_string(ItemList[i].ItemData.NumStack), Color::White);

					if (ItemList[i].ItemData.ItemName == LastItemName && ItemList[i].ItemData.bIsStackable)
					{
						GEngine->Print(" | Restores " + std::to_string(ItemList[i].ItemData.Amount) + "hp", Color::White);
					}


					GEngine->PrintBlankLines(1);
				}
			}

			GEngine->WaitForKey();
			PrintMenu();   // redraw the town menu
			break;
		}
		case 4:
			PlayerLeaderboard(player);
			break;
		case 5:
			if (player.charStats.Health <= 0) 
			{
				GEngine->Print("Your health is at 0! I recommend taking a long rest first!");
			}
			else
			{
				bSafeZone = false;
			}
			break;
		case 6:
			session.RequestSessionEnd();
			SaveSystem::SaveGame(player);
			GEngine->ClearConsole();
			Input::FlushInput();
			bSafeZone = false;
			break;
		default:
			break;
		}
	}

	Input::FlushInput();
}
 
void Town::LongRest(Player& player)
{
	GEngine->TypeOut("For the night, you stayed at the local inn. Recovering all your strength!", 15ms, 1000ms, Color::Cyan, 1);
	player.charStats.Health = player.charStats.MaxHealth;
	return;
}

void Town::PlayerLeaderboard(Player& player)
{
	GEngine->Print("<=><=><=><=><=> Player Leaderboard <=><=><=><=><=>", Color::Blue, 2);
	GEngine->Print("Total Wins: " + std::to_string(player.playerLeaderboard.TotalWins), Color::Green, 1);
	GEngine->Print("Total Loses: " + std::to_string(player.playerLeaderboard.TotalLoss), Color::Green, 1);
	GEngine->Print("Total Damage Given: " + std::to_string(player.playerLeaderboard.TotalDamageGiven), Color::Green, 1);
	GEngine->Print("Total Damage Recieved: " + std::to_string(player.playerLeaderboard.TotalDamageTaken), Color::Red, 1);


	GEngine->WaitForKey();

	GEngine->ClearLastLine(8);
}

void Town::PrintMenu() const
{
	GEngine->ClearConsole();
	GEngine->Print("<=><=><=><=><=> " + currentTownName + " <=><=><=><=><=>", Color::Blue, 2);
	GEngine->TypeOut("Please select an option", 15ms, 1000ms, Color::Blue, 1);
	GEngine->TypeOut("1. Shop", 1ms, 100ms, Color::White, 1);
	GEngine->TypeOut("2. Long Rest", 1ms, 100ms, Color::White, 1);
	GEngine->TypeOut("3. Your Bag", 1ms, 100ms, Color::White, 1);
	GEngine->TypeOut("4. Player Leaderboard", 1ms, 100ms, Color::White, 1);
	GEngine->TypeOut("5. Exit Safe Zone", 1ms, 100ms, Color::White, 1);
	GEngine->TypeOut("6. Main Menu", 1ms, 500ms, Color::White, 1);
}