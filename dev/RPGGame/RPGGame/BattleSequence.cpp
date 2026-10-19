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
		GEngine->TypeOut("Oh no!! You have been ambushed!!", 30ms, 1000ms, Color::Gray, 1);

		CreateEnemies(); // Creates a random enemy
		RollForInitiative(player); // Each character (enemies and player) will roll to dictate the turn order
		RunCombat(player);     // the stats table is shown at the start of each player turn

		enemyList.clear(); // clears the enemyList
		turnOrder.clear(); // clears the turn order
		GEngine->ProcessDeferredDestruction();

		// Don't start another fight if the player is dead
		if (!IsAlive(&player))
		{
			break;
		}

		GEngine->ClearConsole();
	}
}

void BattleSequence::CreateEnemies()
{
	// Randomly selects a number that ranges between the inputed values
	int numOfEnemy = UMath::RandRange(1, 3); // Chooses a number between the given values that determine how many enemies the player will face

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

	for (Character* c : turnOrder)
	{
		GEngine->Print("Name: " + c->charStats.Name + " | Initiative: " + std::to_string(c->Initiative()), Color::Blue, 1);
	}

	GEngine->WaitForKey(); // Waits for the user to enter any key to continue
}


// Shows your stats on the left and every enemy in the battle on the right
void BattleSequence::CharacterStats(Player& player, const std::vector<Character*>& enemies) const
{
	const size_t columnWidth = 40; // how far over the enemy column starts

	// Adds spaces to the end of text so the right column lines up
	auto padRight = [columnWidth](std::string text)
		{
			if (text.size() < columnWidth)
			{
				text += std::string(columnWidth - text.size(), ' ');
			}
			return text;
		};

	GEngine->Print(padRight("<=><=><=> Your Team <=><=><=>"), Color::Green, 0);
	GEngine->Print("<=><=><=> Enemy Team <=><=><=>", Color::Red, 1);

	// Lines for the left column
	std::vector<std::string> playerLines;
	playerLines.push_back("You: " + player.charStats.Name);
	playerLines.push_back("Health: " + std::to_string(player.charStats.Health));
	playerLines.push_back("Stamina: " + std::to_string(player.charStats.Stamina));

	// Lines for the right column (one per enemy)
	std::vector<std::string> enemyLines;
	for (Character* e : enemies)
	{
		if (IsAlive(e))
		{
			enemyLines.push_back(e->charStats.Name + " | Health: " + std::to_string(e->charStats.Health));
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

		GEngine->Print(padRight(left), Color::Green, 0);
		GEngine->Print(right, Color::Red, 1);
	}

	GEngine->Print("", Color::White, 1);
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
	while (true)
	{
		int BOM = Menus::BattleOptionsMenu();

		if (BOM == 1)
		{
			Character* target = ChooseTarget(enemies);   // player picks who to hit
			player.playerLeaderboard.TotalDamageGiven += player.charStats.Attack;
			Attack(&player, target, player.charStats.Attack);
			return; // turn used
		}
		else if (BOM == 2)
		{
			Abilities(player, enemies);   // Abilities picks the target itself
			return; // turn used
		}
		else if (BOM == 4)
		{
		}
		else
		{
			// Options 3 and 4 aren't built yet, so show the menu again
			GEngine->Print("That option isn't available yet.", Color::Gray, 1);
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


	int round = 1;
	
	while (IsAlive(&player) && AnyAlive(enemies))
	{
		GEngine->ClearConsole();

		GEngine->Print("<=><=><=> CHARACTER STATS <=><=><=>" + std::to_string(round) + " ---", Color::Blue, 1);
		statsRow = GetCursorRow();          // remember where the panel starts
		CharacterStats(player, enemies);

		GEngine->Print("--- Round " + std::to_string(round) + " ---", Color::Blue, 1);



		for (Character* c : turnOrder)
		{
			if (!IsAlive(c))
			{
				continue; // dead characters skip their turn
			}

			if (c == &player)
			{
				PlayerTurn(player, enemies);
			}
			else
			{
				EnemyTurn(c, player);
			}

			DrawStatsAtTop(player, enemies);

			GEngine->WaitForKey();

			// Stop as soon as one side is wiped out
			if (!IsAlive(&player) || !AnyAlive(enemies))
			{
				break;
			}


		}

		round++;
	}

	if (IsAlive(&player))
	{
		GEngine->TypeOut("Victory! All enemies have been defeated!", 30ms, 1000ms, Color::Cyan, 1);
		player.playerLeaderboard.TotalWins += 1;
	}
	else
	{
		GEngine->TypeOut("You have fallen...", 30ms, 1000ms, Color::Red, 1);
		player.playerLeaderboard.TotalLoss += 1;
	}

	GEngine->WaitForKey();
}

// The player's turn: show everyone's stats, then the battle menu
void BattleSequence::PlayerTurn(Player& player, const std::vector<Character*>& enemies)
{
	BattleMenu(player, enemies);
}

// Lists the living enemies and returns the one the player picks
Character* BattleSequence::ChooseTarget(const std::vector<Character*>& enemies)
{
	std::vector<Character*> targets;

	for (Character* e : enemies)
	{
		if (IsAlive(e))
		{
			targets.push_back(e);
		}
	}

	GEngine->Print("Choose a target:", Color::White, 1);

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
	GEngine->Print("Choose an Ability:", Color::White, 1);

	int abilityCount = static_cast<int>(player.charAbilities.abilities.size());

	for (int i = 0; i < abilityCount; i++)
	{
		GEngine->Print(std::to_string(i + 1) + ". " + player.charAbilities.abilities[i].Name
			+ " | Damage: " + std::to_string(player.charAbilities.abilities[i].Damage), Color::White, 1);
	}

	int spellChoice = Input::GetInput(">> ", 1, abilityCount);
	int damage = player.charAbilities.abilities[spellChoice - 1].Damage;

	Character* target = ChooseTarget(enemies);

	player.playerLeaderboard.TotalDamageGiven += damage;
	Attack(&player, target, damage);
}

void BattleSequence::EnemyTurn(Character* enemy, Player& player)
{
	int healthBefore = player.charStats.Health;

	Attack(enemy, &player, enemy->charStats.Attack);

	// Count the damage actually taken (health can't go below 0)
	player.playerLeaderboard.TotalDamageTaken += healthBefore - player.charStats.Health;
}


void BattleSequence::Attack(Character* attacker, Character* target, int damage)
{
	target->charStats.Health = UMath::Clamp(target->charStats.Health - damage, 0, target->charStats.MaxHealth);

	GEngine->TypeOut(attacker->charStats.Name + " attacks " + target->charStats.Name
		+ " for " + std::to_string(damage) + " damage!", 15ms, 500ms, Color::Gray, 1);

	if (!IsAlive(target))
	{
		GEngine->TypeOut(target->charStats.Name + " has been defeated!", 15ms, 500ms, Color::Red, 1);
	}
}

bool BattleSequence::IsAlive(const Character* character) const
{
	return character->charStats.Health > 0;
}

bool BattleSequence::AnyAlive(const std::vector<Character*>& characters) const
{
	for (const Character* c : characters)
	{
		if (IsAlive(c))
		{
			return true;
		}
	}

	return false;
}

short BattleSequence::GetCursorRow() const
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	return info.dwCursorPosition.Y;
}
