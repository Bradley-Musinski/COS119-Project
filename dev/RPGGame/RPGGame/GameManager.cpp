#include <iostream>
#include "GameManager.h"
#include "GameEngine.h"
#include "GameSession.h"
#include "SaveSystem.h"
#include "Menus.h"

void GameManager::MainMenu()
{
	GameSession Session;

	while (GEngine->IsRunning())
	{
		int MenuChoice = Menus::MainMenu();

		if (MenuChoice == 4)
		{
			GEngine->RequesetQuit(); // Calls a function inside of the engine that flips a bool to false

		}
		if (MenuChoice == 1)
		{
			Session.SetIsNewGame(); // Calls a function inside the session that flips a bool to true
			Session.StartSession(); // Starts the session
		}

		if (MenuChoice == 2)
		{
			std::string saveFile = LoadGame();

			if (saveFile != "")
			{
				Session.SetSaveFile(saveFile);
				Session.StartSession();
			}
		}
	}	
}

std::string GameManager::LoadGame()
{
	std::vector<std::string> saves = SaveSystem::GetSaveFiles();

	// No saves: tell the player and go back to the main menu
	if (saves.size() == 0)
	{
		std::cout << "No save data found.\n";
		std::this_thread::sleep_for(2s);
		GEngine->ClearConsole();
		return "";
	}

	// Show every save file
	GEngine->Print("<=><=><=> LOAD GAME <=><=><=>", Color::Green, 1);

	GEngine->Print("::  Type the name of the save you wish to load, then press ENTER. ::", Color::Green, 2);

	for (int i = 0; i < saves.size(); i++)
	{
		GEngine->Print("{" + std::to_string(i + 1) + "} " + saves[i], Color::White, 1);
	}

	GEngine->PrintBlankLines(1);
	GEngine->Print(":: Type '0' then ENTER to go back to the MAIN MENU ::", Color::Green, 1);
	GEngine->Print(">> ", Color::White, 0);
	std::string name;
	std::getline(std::cin >> std::ws, name); // reads the whole name, even with spaces

	// Typed 0: go back to the main menu
	if (name == "0")
	{
		GEngine->ClearConsole();
		return "";
	}

	// Look for a save with that name
	for (int i = 0; i < saves.size(); i++)
	{
		if (saves[i] == name)
		{
			return "SavedGames/" + saves[i] + ".txt";
		}
	}

	GEngine->Print("No save found with that name...", Color::White, 1);
	return "";
}


