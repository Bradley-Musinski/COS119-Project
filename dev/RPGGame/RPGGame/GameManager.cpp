#include "GameManager.h"
#include "GameEngine.h"
#include "GameSession.h"
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
			LoadGame(); // Loads data from a previous save
			Session.StartSession(); // Starts the session
		}
	}
	
}

void GameManager::LoadGame()
{
	// This will eventually load player save data
}


