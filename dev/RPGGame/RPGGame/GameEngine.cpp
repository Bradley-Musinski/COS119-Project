#include <algorithm>
#include "GameEngine.h"
#include "GameManager.h"
#include "AActor.h"

GameEngine* GEngine = nullptr; // Sets the Global GameEngine pointer to nullptr

// Destructor
GameEngine::~GameEngine()
{
	bIsRunning = false;
	for (AActor* actor : ActorRegistry)
	{
		delete actor;
	}
	ActorRegistry.clear();
}

void GameEngine::Run()
{
	bIsRunning = true;

	GameManager manager;

	manager.MainMenu();
}


void GameEngine::ProcessDeferredDestruction()
{
	for (auto it = ActorRegistry.begin(); it != ActorRegistry.end(); ) {
		if ((*it)->PendingDestruction()) {

			// This frees up the memory then vaporizes the pointer out of existence
			delete* it;
			it = ActorRegistry.erase(it);
			Print("Actor was destroyed", Color::Red, 1);
		}
		else {
			++it;
		}		
	}
}

void GameEngine::RegisterActor(AActor* actor)
{
	if (std::find(ActorRegistry.begin(), ActorRegistry.end(), actor) == ActorRegistry.end())
	{
		ActorRegistry.push_back(actor);
	}
}

void GameEngine::PrintBlankLines(int numOfBlankLines)
{
	for (int i = 0; i < numOfBlankLines; i++)
	{ 
		std::cout << std::endl;
	}

}

void GameEngine::ErrorMessage(std::string message)
{
	TypeOut(message, 1ms, 1s, Color::Red, 1);
}

void GameEngine::ClearLastLine(int LineAmt)
{
	for (int i = 0; i < LineAmt; i++)
	{
		Print("\x1b[1A\x1b[2K\r", Color::White, 0);
	}

}

void GameEngine::WaitForKey()
{
	Print("Press any key to continue...", Color::Gray);
#ifdef _WIN32
	if (_getch()) // waits for any key instead
	{
		PrintBlankLines(1);
	}
#else
	std::cin.get(); // waits for Enter instead
#endif
}

void GameEngine::ClearConsole()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

