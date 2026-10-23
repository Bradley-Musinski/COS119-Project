#define NOMINMAX
#include <windows.h>
#include <string>
#include <vector>
#include <algorithm>
#include "BattleSequence.h"
#include "Player.h"
#include "Enemy.h"
#include "Skeleton.h"
#include "Goblin.h"
#include "Kobald.h"
#include "Input.h"
#include "Menus.h"
#include <thread>

using namespace std::chrono_literals;

// Destructor
BattleSequence::~BattleSequence()
{

}


void BattleSequence::Battle(Player& player)
{
	GEngine->ClearConsole();

	int RandNum = UMath::RandRange(1, 3);

	for (int i = 0; i < RandNum; i++)
	{
		GEngine->Print("<=><=><=><=><=><=><=> FIGHT <=><=><=><=><=><=><=>", Color::BMagenta, 1);
		GEngine->TypeOut("As you were walking down the road, enemies leap out from the shadows!", 30ms, 1000ms, Color::Gray, 1);

		CreateEnemies(); // Creates a random enemy
		RollForInitiative(player); // Each character (enemies and player) will roll to dictate the turn order
		RunCombat(player);     // the stats table is shown at the start of each player turn

		enemyList.clear(); // clears the enemyList
		turnOrder.clear(); // clears the turn order
		GEngine->ProcessDeferredDestruction();

		// Don't start another fight if the player is dead
		if (!player.IsAlive())
		{
			break;
		}

		GEngine->ClearConsole();
	}
}

void BattleSequence::CreateEnemies()
{
	// Randomly selects a number that ranges between the inputed values
	int numOfEnemy = UMath::RandRange(1, 2); // Chooses a number between the given values that determine how many enemies the player will face

	for (int i = 0; i < numOfEnemy; i++)
	{
		// Chooses a number between the given values that determines which enemies the player will face
		int randNum = UMath::RandRange(1, 3); 

		if (randNum == 1)
		{
			enemyList.push_back(new Skeleton());
		}
		else if (randNum == 2)
		{
			enemyList.push_back(new Goblin());
		}
		else
		{
			enemyList.push_back(new Kobald());
		}
	}
}

// Each character rolls to decide the turn order (Highest goes first, lowest last)
// then the order is printed for the player
void BattleSequence::RollForInitiative(Player& player)
{
	turnOrder.push_back(&player);

	// Only the enemies in THIS battle get a turn
	for (Enemy* enemy : enemyList)
	{
		turnOrder.push_back(enemy);
	}

	for (Character* character : turnOrder)
	{
		character->RollInitiative();
	}

	std::sort(turnOrder.begin(), turnOrder.end(),
		[](Character* a, Character* b) { return a->Initiative() > b->Initiative(); });

	GEngine->Print("<=><=><=> TURN ORDER <=><=><=>", Color::Blue, 1);

	for (Character* c : turnOrder)
	{
		GEngine->Print("Name: " + c->charStats.Name + " | Initiative: " + std::to_string(c->Initiative()), Color::Blue, 1);
	}

	GEngine->WaitForKey(); // Waits for the user to enter any key to continue
}


// Shows your stats on the left and every enemy in the battle on the right
void BattleSequence::CharacterStats(Player& player, const std::vector<Character*>& enemies) const
{
	const size_t leftWidth = 40;  // how far over the enemy column starts
	const size_t rightWidth = 40; // wide enough for the longest enemy line

	// Adds spaces to the end of text so it always takes up the same width.
	// That way, redrawing a shorter line still covers the old one.
	auto pad = [](std::string text, size_t width)
		{
			if (text.size() < width)
			{
				text += std::string(width - text.size(), ' ');
			}
			return text;
		};

	GEngine->Print(pad("<=><=><=> Your Team <=><=><=>", leftWidth), Color::Green, 0);
	GEngine->Print(pad("<=><=><=> Enemy Team <=><=><=>", rightWidth), Color::Red, 1);

	// Lines for the left column (health clamped so it never shows below 0)
	std::vector<std::string> playerLines;
	playerLines.push_back("You: " + player.charStats.Name);
	playerLines.push_back("Health: " + std::to_string(std::max(0, player.charStats.Health)));
	playerLines.push_back("Stamina: " + std::to_string(player.charStats.Stamina));

	// Lines for the right column (one per enemy)
	std::vector<std::string> enemyLines;
	for (Character* e : enemies)
	{
		if (e->IsAlive())
		{
			enemyLines.push_back(e->charStats.Name + " | Health: " + std::to_string(std::max(0, e->charStats.Health)));
		}
		else
		{
			enemyLines.push_back(e->charStats.Name + " | DEFEATED");
		}
	}

	// Print both columns side by side, row by row
	size_t rows = std::max(playerLines.size(), enemyLines.size());

	for (size_t i = 0; i < rows; i++)
	{
		std::string left = (i < playerLines.size()) ? playerLines[i] : "";
		std::string right = (i < enemyLines.size()) ? enemyLines[i] : "";

		GEngine->Print(pad(left, leftWidth), Color::Green, 0);
		GEngine->Print(pad(right, rightWidth), Color::Red, 1);
	}

	GEngine->Print("", Color::White, 1);
}

void BattleSequence::DrawBattleScreen(Player& player, const std::vector<Character*>& enemies, int round) const
{
	GEngine->ClearConsole();

	GEngine->Print("<=><=><=><=><=><=><=> CHARACTER STATS <=><=><=><=><=><=><=>", Color::Gold, 2);
	CharacterStats(player, enemies);
	GEngine->Print("<=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=>", Color::Gold, 2);

	GEngine->Print("--- Round " + std::to_string(round) + " ---", Color::Gold, 1);
}

void BattleSequence::DrawStatsAtTop(Player& player, const std::vector<Character*>& enemies) const
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	// Remember where the cursor was
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(console, &info);
	COORD saved = info.dwCursorPosition;

	// Jump to the row where the stats were first drawn
	SetConsoleCursorPosition(console, COORD{ 0, statsRow });
	CharacterStats(player, enemies);

	// Go back to where the battle text was
	SetConsoleCursorPosition(console, saved);
}

// Shows the battle options. Loops until the player picks something that uses their turn.
void BattleSequence::BattleMenu(Player& player, const std::vector<Character*>& enemies)
{
	Input::FlushInput();
	GEngine->TypeOut(":: It's your turn! ::", 30ms, 1000ms, Color::Green, 1);

	while (true)
	{

		GEngine->TypeOut(":: Type an Option from Below ::", 30ms, 1000ms, Color::Green, 1);
		GEngine->TypeOut(": Basic Attack", 1ms, 1ms, Color::Green, 1);
		GEngine->TypeOut(": Abilities", 1ms, 1ms, Color::Green, 1);
		GEngine->TypeOut(": Bag", 1ms, 1ms, Color::Green, 1);
		GEngine->TypeOut(">> ", 1ms, 1ms, Color::White, 0);

		std::string BOM;
		getline(std::cin, BOM);

		GEngine->PrintBlankLines(1);

		if (BOM == "Basic Attack")
		{
			Character* target = ChooseTarget(enemies);   // player picks who to hit
			player.playerLeaderboard.TotalDamageGiven += player.charStats.Attack;
			player.Attack(&player, target, player.charStats.Attack);
			return; // turn used
		}
		else if (BOM == "Abilities")
		{
			Abilities(player, enemies);   // Abilities picks the target itself
			return; // turn used
		}
		else if (BOM == "Bag")
		{
			if (Bag(player))
			{
				return; // item used, turn over
			}
		}
		else
		{
			GEngine->ErrorMessage("ERROR: Please choose an option from above");
			std::this_thread::sleep_for(2s);
			GEngine->ClearLastLine(7);
		}
	}
}

// Runs the fight using the initiative order from RollForInitiative
void BattleSequence::RunCombat(Player& player)
{
	// The other functions take Character*, so copy the Enemy* pointers into a Character* list
	std::vector<Character*> enemies;

	for (Enemy* enemy : enemyList)
	{
		enemies.push_back(enemy);
	}

	GEngine->ClearConsole();
	GEngine->Print("<=><=><=><=><=> BATTLE START <=><=><=><=><=>", Color::BMagenta, 1);
	std::this_thread::sleep_for(1s);

	int round = 1;

	while (player.IsAlive() && Character::AnyAlive(enemies))
	{
		for (Character* c : turnOrder)
		{
			if (!c->IsAlive())
			{
				continue; // dead characters skip their turn
			}

			// Fresh screen with up-to-date stats before every turn
			DrawBattleScreen(player, enemies, round);

			if (c == &player)
			{
				player.TakeTurn(player, enemies);
			}
			else
			{
				static_cast<Enemy*>(c)->TakeTurn(player);
			}

			GEngine->WaitForKey();

			// Stop as soon as one side is wiped out
			if (!player.IsAlive() || !Character::AnyAlive(enemies))
			{
				break;
			}
		}

		round++;
	}

	// Show the final stats once more before the win/loss message
	DrawBattleScreen(player, enemies, round - 1);

	if (player.IsAlive())
	{
		GEngine->TypeOut(" :: Victory! All enemies have been defeated! ::", 30ms, 1000ms, Color::Cyan, 1);
		player.playerLeaderboard.TotalWins += 1;
	}
	else
	{
		GEngine->TypeOut(":: You have fallen... ::", 30ms, 1000ms, Color::Red, 1);
		player.playerLeaderboard.TotalLoss += 1;
	}

	GEngine->WaitForKey();
}

// Lists the living enemies and returns the one the player picks
Character* BattleSequence::ChooseTarget(const std::vector<Character*>& enemies) const
{
	std::vector<Character*> targets;

	for (Character* e : enemies)
	{
		if (e->IsAlive())
		{
			targets.push_back(e);
		}
	}

	GEngine->Print(":: Choose a Target by Entering the Number Next to the Enemy ::", Color::White, 1);

	for (size_t i = 0; i < targets.size(); i++)
	{
		GEngine->Print(std::to_string(i + 1) + ". " + targets[i]->charStats.Name
			+ " | Health: " + std::to_string(targets[i]->charStats.Health), Color::White, 1);
	}

	int targetChoice = Input::GetInput(">> ", 1, static_cast<int>(targets.size()));
	return targets[targetChoice - 1];
}

void BattleSequence::Abilities(Player& player, const std::vector<Character*>& enemies)
{
	// 1. Pick a spell
	GEngine->Print(":: Choose an Ability ::", Color::White, 1);

	int abilityCount = static_cast<int>(player.charAbilities.abilities.size());

	for (int i = 0; i < abilityCount; i++)
	{
		GEngine->Print(std::to_string(i + 1) + ". " + player.charAbilities.abilities[i].Name
			+ " | Damage: " + std::to_string(player.charAbilities.abilities[i].MinDamage) + " - " + std::to_string(player.charAbilities.abilities[i].MaxDamage), Color::White, 1);
	}

	int spellChoice = Input::GetInput(">> ", 1, abilityCount);
	

	Character* target = ChooseTarget(enemies);


	if (player.RollToHit(target))
	{
		int damage = UMath::RandRange(player.charAbilities.abilities[spellChoice - 1].MinDamage, player.charAbilities.abilities[spellChoice - 1].MaxDamage);

		GEngine->Print(player.charAbilities.abilities[spellChoice - 1].Name + " hits " + target->charStats.Name
			+ " for " + std::to_string(damage) + "!", Color::Green, 1);


		player.playerLeaderboard.TotalDamageGiven += damage;
		player.Attack(&player, target, damage);
	}
	else
	{
		GEngine->Print(":: " + player.charAbilities.abilities[spellChoice - 1].Name + " misses "
			+ target->charStats.Name + "! ::", Color::Gray, 1);
	}


}

bool BattleSequence::Bag(Player& player)
{
	const std::vector<Item>& ItemList = player.character.GetItems();

	if (ItemList.empty())
	{
		GEngine->Print(":: Your inventory is empty ::", Color::White, 1);
		system("pause");
		GEngine->ClearLastLine(8);
		return false;
	}

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

	while (true)
	{
		GEngine->Print(":: Which Item Would You Like to Use? (type the item you wish to use or 'back' to cancel) ::", Color::Green, 1);

		std::string typed;
		std::getline(std::cin, typed);

		if (typed.empty())
		{
			continue;
		}

		if (typed == "back")
		{
			GEngine->ClearLastLine(8 + static_cast<int>(ItemList.size()));
			return false;
		}

		for (const Item& item : ItemList)
		{
			if (item.ItemData.ItemName == typed)
			{
				Item usedItem = item;
				usedItem.UseItem(player);
				player.character.RemoveItem(usedItem);
				system("pause");
				return true;
			}
		}

		GEngine->Print(":: You don't have that item. ::", Color::Red, 1);
		std::this_thread::sleep_for(2s);
		GEngine->ClearLastLine(3);
	}

	system("pause");
}

short BattleSequence::GetCursorRow() const
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	return info.dwCursorPosition.Y;
}
