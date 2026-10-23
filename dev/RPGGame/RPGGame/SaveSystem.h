#pragma once
#include <fstream>
#include <string>
#include <random>
#include <filesystem>
#include "Player.h"

namespace SaveSystem
{
	// Makes a name like "SavedGames/[Player Name Here].txt"
	inline std::string MakeFileName(const std::string& playerName)
	{
		return "SavedGames/" + playerName + ".txt";
	}

	// Saves the player and returns the file name it used ("" if it failed)
	inline std::string SavePlayer(const Player& player)
	{
		// Make the folder if it doesn't exist yet
		std::filesystem::create_directories("SavedGames");

		std::string fileName = MakeFileName(player.charStats.Name);
		std::ofstream file(fileName);

		if (!file.is_open())
		{
			return "";
		}

		// Stats
		file << player.charStats.Name << "\n";
		file << player.charStats.ClassName << "\n";
		file << player.charStats.Health << "\n";
		file << player.charStats.MaxHealth << "\n";
		file << player.charStats.Attack << "\n";
		file << player.charStats.ArmorClass << "\n";
		file << player.charStats.Stamina << "\n";
		file << player.charStats.Exp << "\n";

		// Leaderboard
		file << player.playerLeaderboard.TotalWins << "\n";
		file << player.playerLeaderboard.TotalLoss << "\n";
		file << player.playerLeaderboard.TotalDamageGiven << "\n";
		file << player.playerLeaderboard.TotalDamageTaken << "\n";

		// Inventory
		file << player.character.GetGold() << "\n";
		file << player.character.Items.size() << "\n";
		for (const Item& item : player.character.Items)
		{
			file << item.ItemData.ItemName << "\n";
			file << item.ItemData.ItemID << "\n";
			file << item.ItemData.ItemValue << "\n";
			file << item.ItemData.bIsStackable << "\n";
			file << item.ItemData.MaxStack << "\n";
			file << item.ItemData.NumStack << "\n";
			file << item.ItemData.Amount << "\n";
			file << static_cast<int>(item.ItemData.Type) << "\n";
		}

		// Abilities
		file << player.charAbilities.abilities.size() << "\n";
		for (const CharacterAbility& ability : player.charAbilities.abilities)
		{
			file << ability.Name << "\n";
			file << ability.Desc << "\n";
			file << ability.MinDamage << "\n";
			file << ability.MaxDamage << "\n";
			file << ability.Health << "\n";
			file << ability.Armor << "\n";
			file << ability.cost << "\n";
		}

		file.close();
		return fileName;
	}

	// Loads a save file into the player. Returns false if the file couldn't be opened.
	inline bool LoadPlayer(Player& player, const std::string& fileName)
	{
		std::ifstream file(fileName);

		if (!file.is_open())
		{
			return false;
		}

		// Stats (getline so names with spaces work)
		std::getline(file, player.charStats.Name);
		std::getline(file, player.charStats.ClassName);
		file >> player.charStats.Health;
		file >> player.charStats.MaxHealth;
		file >> player.charStats.Attack;
		file >> player.charStats.ArmorClass;
		file >> player.charStats.Stamina;
		file >> player.charStats.Exp;

		// Leaderboard
		file >> player.playerLeaderboard.TotalWins;
		file >> player.playerLeaderboard.TotalLoss;
		file >> player.playerLeaderboard.TotalDamageGiven;
		file >> player.playerLeaderboard.TotalDamageTaken;

		// Inventory
		int gold = 0;
		file >> gold;
		player.character.SetGold(gold);

		int itemCount = 0;
		file >> itemCount;

		player.character.Items.clear();
		for (int i = 0; i < itemCount; i++)
		{
			Item item;
			int type = 0;

			std::getline(file >> std::ws, item.ItemData.ItemName); // names can have spaces, like "Health Potion"
			file >> item.ItemData.ItemID;
			file >> item.ItemData.ItemValue;
			file >> item.ItemData.bIsStackable;
			file >> item.ItemData.MaxStack;
			file >> item.ItemData.NumStack;
			file >> item.ItemData.Amount;
			file >> type;
			item.ItemData.Type = static_cast<ItemType>(type);

			player.character.Items.push_back(item);
		}

		// Abilities
		int abilityCount = 0;
		file >> abilityCount;

		player.charAbilities.abilities.clear();
		for (int i = 0; i < abilityCount; i++)
		{
			CharacterAbility ability;

			std::getline(file >> std::ws, ability.Name); // "Eldritch Blast" has a space
			std::getline(file >> std::ws, ability.Desc); // descriptions are full sentences
			file >> ability.MinDamage;
			file >> ability.MaxDamage;
			file >> ability.Health;
			file >> ability.Armor;
			file >> ability.cost;

			player.charAbilities.abilities.push_back(ability);
		}

		file.close();
		return true;
	}

	inline void SaveGame(Player& player)
	{
		SavePlayer(player);
	}

	inline std::vector<std::string> GetSaveFiles()
	{
		std::vector<std::string> saves;

		if (!std::filesystem::exists("SavedGames"))
		{
			return saves;
		}

		for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator("SavedGames"))
		{
			if (entry.path().extension() == ".txt")
			{
				saves.push_back(entry.path().stem().string());
			}
		}

		return saves;
	}

}